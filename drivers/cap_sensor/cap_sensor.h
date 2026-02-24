#ifndef CAP_SENSOR_H
#define CAP_SENSOR_H

#include <stdint.h>

struct cap_sensor_data {
	uint16_t raw_value;
	uint8_t touch_detected;
	uint16_t threshold;
};

int cap_sensor_init(void);
int cap_sensor_read(struct cap_sensor_data *data);
int cap_sensor_set_threshold(uint16_t threshold);
int cap_sensor_is_touched(void);

#endif /* CAP_SENSOR_H */
