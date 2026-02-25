#ifndef CAP_SENSOR_H
#define CAP_SENSOR_H

#include <stdint.h>

/* Register addresses */
#define CAP_SENSOR_REG_T_MSB               0x00    /* Temperature data MSB (R) */
#define CAP_SENSOR_REG_T_LSB               0x01    /* Temperature data LSB (R) */
#define CAP_SENSOR_REG_D0_MSB              0x02    /* Channel 0 data MSB (R) */
#define CAP_SENSOR_REG_D0_LSB              0x03    /* Channel 0 data LSB (R) */
#define CAP_SENSOR_REG_D1_MSB              0x04    /* Channel 1 data MSB (R) */
#define CAP_SENSOR_REG_D1_LSB              0x05    /* Channel 1 data LSB (R) */
#define CAP_SENSOR_REG_D2_MSB              0x06    /* Channel 2 data MSB (R) */
#define CAP_SENSOR_REG_D2_LSB              0x07    /* Channel 2 data LSB (R) */
#define CAP_SENSOR_REG_D3_MSB              0x08    /* Channel 3 data MSB (R) */
#define CAP_SENSOR_REG_D3_LSB              0x09    /* Channel 3 data LSB (R) */
#define CAP_SENSOR_REG_D4_MSB              0x0A    /* Channel 4 data MSB (R) */
#define CAP_SENSOR_REG_D4_LSB              0x0B    /* Channel 4 data LSB (R) */
#define CAP_SENSOR_REG_D5_MSB              0x0C    /* Channel 5 data MSB (R) */
#define CAP_SENSOR_REG_D5_LSB              0x0D    /* Channel 5 data LSB (R) */
#define CAP_SENSOR_REG_D6_MSB              0x0E    /* Channel 6 data MSB (R) */
#define CAP_SENSOR_REG_D6_LSB              0x0F    /* Channel 6 data LSB (R) */
#define CAP_SENSOR_REG_D7_MSB              0x10    /* Channel 7 data MSB (R) */
#define CAP_SENSOR_REG_D7_LSB              0x11    /* Channel 7 data LSB (R) */
#define CAP_SENSOR_REG_D8_MSB              0x12    /* Channel 8 data MSB (R) */
#define CAP_SENSOR_REG_D8_LSB              0x13    /* Channel 8 data LSB (R) */
#define CAP_SENSOR_REG_D9_MSB              0x14    /* Channel 9 data MSB (R) */
#define CAP_SENSOR_REG_D9_LSB              0x15    /* Channel 9 data LSB (R) */
#define CAP_SENSOR_REG_DREF_MSB            0x16    /* Reference data MSB (R) */
#define CAP_SENSOR_REG_DREF_LSB            0x17    /* Reference data LSB (R) */
#define CAP_SENSOR_REG_OSC1_OF_MSB         0x18    /* OSC1 overflow MSB (R) */
#define CAP_SENSOR_REG_OSC1_OF_LSB         0x19    /* OSC1 overflow LSB (R) */
#define CAP_SENSOR_REG_OSC2_OF             0x1A    /* OSC2 overflow (R) */
#define CAP_SENSOR_REG_STATUS              0x1B    /* Status register (R/W) */
#define CAP_SENSOR_REG_T_CMD               0x1C    /* Temperature command (R/W) */
#define CAP_SENSOR_REG_C_CMD               0x1D    /* Capacitance command (R/W) */
#define CAP_SENSOR_REG_CNT_CFG             0x1E    /* Count configuration (R/W) */
#define CAP_SENSOR_REG_DIV_CFG             0x1F    /* Divider configuration (R/W) */
#define CAP_SENSOR_REG_OSC1_CHS_MSB        0x20    /* OSC1 channels MSB (R/W) */
#define CAP_SENSOR_REG_OSC1_CHS_LSB        0x21    /* OSC1 channels LSB (R/W) */
#define CAP_SENSOR_REG_OSC1_MCHS           0x22    /* OSC1 mutual capacitance channels (R/W) */
#define CAP_SENSOR_REG_OSC1_CFG            0x23    /* OSC1 configuration (R/W) */
#define CAP_SENSOR_REG_OSC2_DCHS           0x24    /* OSC2 differential channels (R/W) */
#define CAP_SENSOR_REG_OSC2_CFG            0x25    /* OSC2 configuration (R/W) */
#define CAP_SENSOR_REG_SHLD_CFG            0x26    /* Shield configuration (R/W) */
#define CAP_SENSOR_REG_RESET               0x69    /* Soft reset (W) */
#define CAP_SENSOR_REG_CHIP_ID_MSB         0x7E    /* Chip ID MSB (R) */
#define CAP_SENSOR_REG_CHIP_ID_LSB         0x7F    /* Chip ID LSB (R) */

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
