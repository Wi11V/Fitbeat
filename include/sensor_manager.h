#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <stdint.h>

struct sensor_data {
	/* BMI270 data */
	struct {
		float accel_x, accel_y, accel_z;
		float gyro_x, gyro_y, gyro_z;
		float mag_x, mag_y, mag_z;
	} imu;

	/* High-G accelerometer */
	struct {
		float accel_x, accel_y, accel_z;
	} highg_accel;

	/* Capacitive sensor */
	uint16_t cap_value;

	/* ADC values */
	uint16_t adc_ch0, adc_ch1, adc_ch2;

	/* Timestamp */
	uint32_t timestamp;
};

int sensor_manager_init(void);
int sensor_manager_read(void);
struct sensor_data* sensor_manager_get_data(void);

#endif /* SENSOR_MANAGER_H */
