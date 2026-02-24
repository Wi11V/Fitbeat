#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(sensor_manager);

#include "sensor_manager.h"

int sensor_manager_init(void)
{
	LOG_INF("Initializing sensor manager...");

	/* Initialize each sensor */
	// TODO: Initialize BMI270
	// TODO: Initialize high-G accelerometer
	// TODO: Initialize capacitive sensor
	// TODO: Initialize ADC

	return 0;
}

int sensor_manager_read(void)
{
	/* Read from all sensors */
	// TODO: Read BMI270 data
	// TODO: Read high-G accelerometer data
	// TODO: Read capacitive sensor data
	// TODO: Read ADC values

	return 0;
}

struct sensor_data* sensor_manager_get_data(void)
{
	// TODO: Return aggregated sensor data
	return NULL;
}
