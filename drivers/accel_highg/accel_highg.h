#ifndef ACCEL_HIGHG_H
#define ACCEL_HIGHG_H

#include <stdint.h>

struct accel_highg_data {
	int16_t accel_x, accel_y, accel_z;
	uint8_t status;
};

int accel_highg_init(void);
int accel_highg_read(struct accel_highg_data *data);
int accel_highg_set_range(uint8_t range);
int accel_highg_set_threshold(uint16_t threshold);

#endif /* ACCEL_HIGHG_H */
