#ifndef BMI270_H
#define BMI270_H

#include <stdint.h>

/* BMI270 I2C Address */
#define BMI270_I2C_ADDR 0x68

/* BMI270 Register Addresses */
#define BMI270_REG_CHIP_ID     0x00
#define BMI270_REG_STATUS      0x03
#define BMI270_REG_ACCEL_X_L   0x0C
#define BMI270_REG_ACCEL_X_H   0x0D
#define BMI270_REG_ACCEL_Y_L   0x0E
#define BMI270_REG_ACCEL_Y_H   0x0F
#define BMI270_REG_ACCEL_Z_L   0x10
#define BMI270_REG_ACCEL_Z_H   0x11
#define BMI270_REG_GYRO_X_L    0x12
#define BMI270_REG_GYRO_X_H    0x13
#define BMI270_REG_GYRO_Y_L    0x14
#define BMI270_REG_GYRO_Y_H    0x15
#define BMI270_REG_GYRO_Z_L    0x16
#define BMI270_REG_GYRO_Z_H    0x17

struct bmi270_data {
	int16_t accel_x, accel_y, accel_z;
	int16_t gyro_x, gyro_y, gyro_z;
	int16_t mag_x, mag_y, mag_z;
};

int bmi270_init(void);
int bmi270_read(struct bmi270_data *data);
int bmi270_set_accel_range(uint8_t range);
int bmi270_set_gyro_range(uint8_t range);

#endif /* BMI270_H */
