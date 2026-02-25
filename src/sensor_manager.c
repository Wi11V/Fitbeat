#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(sensor_manager);

#include "sensor_manager.h"
#include "../drivers/bmi270/bmi270.h"
#include "../drivers/accel_highg/accel_highg.h"
#include "../drivers/cap_sensor/cap_sensor.h"
#include "../drivers/adc_gpio/adc_gpio.h"

/* Sensor data storage */
static struct sensor_data current_sensor_data = {0};

/* Driver data structures */
static struct bmi270_data bmi270_data;
static struct accel_highg_data highg_data;
static struct cap_sensor_data cap_data;
static struct adc_gpio_data adc_data;

int sensor_manager_init(void)
{
	int err = 0;
	
	LOG_INF("Initializing sensor manager...");

	/* Initialize BMI270 IMU */
	err = bmi270_init();
	if (err) {
		LOG_ERR("Failed to initialize BMI270 (err %d)", err);
		return err;
	}
	LOG_INF("BMI270 initialized successfully");

	/* Initialize high-G accelerometer */
	err = accel_highg_init();
	if (err) {
		LOG_ERR("Failed to initialize accel_highg (err %d)", err);
		return err;
	}
	LOG_INF("High-G accelerometer initialized successfully");

	/* Initialize capacitive sensor */
	err = cap_sensor_init();
	if (err) {
		LOG_ERR("Failed to initialize cap_sensor (err %d)", err);
		return err;
	}
	LOG_INF("Capacitive sensor initialized successfully");

	/* Initialize ADC GPIO */
	err = adc_gpio_init();
	if (err) {
		LOG_ERR("Failed to initialize ADC/GPIO (err %d)", err);
		return err;
	}
	LOG_INF("ADC/GPIO initialized successfully");

	return 0;
}

int sensor_manager_read(void)
{
	int err = 0;

	/* Read BMI270 data */
	err = bmi270_read(&bmi270_data);
	if (err) {
		LOG_ERR("Failed to read BMI270 (err %d)", err);
	} else {
		/* Convert int16_t to float with scaling factor (typical: 16384 LSB/g for ±2g range) */
		current_sensor_data.imu.accel_x = (float)bmi270_data.accel_x / 16384.0f;
		current_sensor_data.imu.accel_y = (float)bmi270_data.accel_y / 16384.0f;
		current_sensor_data.imu.accel_z = (float)bmi270_data.accel_z / 16384.0f;
		current_sensor_data.imu.gyro_x = (float)bmi270_data.gyro_x / 131.0f;
		current_sensor_data.imu.gyro_y = (float)bmi270_data.gyro_y / 131.0f;
		current_sensor_data.imu.gyro_z = (float)bmi270_data.gyro_z / 131.0f;
		current_sensor_data.imu.mag_x = (float)bmi270_data.mag_x;
		current_sensor_data.imu.mag_y = (float)bmi270_data.mag_y;
		current_sensor_data.imu.mag_z = (float)bmi270_data.mag_z;
	}

	/* Read high-G accelerometer data */
	err = accel_highg_read(&highg_data);
	if (err) {
		LOG_ERR("Failed to read accel_highg (err %d)", err);
	} else {
		current_sensor_data.highg_accel.accel_x = (float)highg_data.accel_x / 256.0f;
		current_sensor_data.highg_accel.accel_y = (float)highg_data.accel_y / 256.0f;
		current_sensor_data.highg_accel.accel_z = (float)highg_data.accel_z / 256.0f;
	}

	/* Read capacitive sensor data */
	err = cap_sensor_read(&cap_data);
	if (err) {
		LOG_ERR("Failed to read cap_sensor (err %d)", err);
	} else {
		current_sensor_data.cap_value = cap_data.raw_value;
	}

	/* Read ADC channels */
	err = adc_gpio_read(&adc_data);
	if (err) {
		LOG_ERR("Failed to read ADC/GPIO (err %d)", err);
	} else {
		current_sensor_data.adc_ch0 = adc_data.adc_ch0;
		current_sensor_data.adc_ch1 = adc_data.adc_ch1;
		current_sensor_data.adc_ch2 = adc_data.adc_ch2;
	}

	/* Update timestamp */
	current_sensor_data.timestamp = k_uptime_get_32();

	return 0;
}

struct sensor_data* sensor_manager_get_data(void)
{
	return &current_sensor_data;
}

