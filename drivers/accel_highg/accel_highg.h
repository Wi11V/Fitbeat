#ifndef ACCEL_HIGHG_H
#define ACCEL_HIGHG_H

#include <stdint.h>

/* Register addresses */
#define ACCEL_HIGHG_REG_DEVID              0x00    /* Device ID (R) */
#define ACCEL_HIGHG_REG_THRESH_SHOCK       0x1D    /* Shock threshold (R/W) */
#define ACCEL_HIGHG_REG_OFSX               0x1E    /* X-axis offset (R/W) */
#define ACCEL_HIGHG_REG_OFSY               0x1F    /* Y-axis offset (R/W) */
#define ACCEL_HIGHG_REG_OFSZ               0x20    /* Z-axis offset (R/W) */
#define ACCEL_HIGHG_REG_DUR                0x21    /* Shock duration (R/W) */
#define ACCEL_HIGHG_REG_LATENT             0x22    /* Shock latency (R/W) */
#define ACCEL_HIGHG_REG_WINDOW             0x23    /* Shock window (R/W) */
#define ACCEL_HIGHG_REG_THRESH_ACT         0x24    /* Activity threshold (R/W) */
#define ACCEL_HIGHG_REG_THRESH_INACT       0x25    /* Inactivity threshold (R/W) */
#define ACCEL_HIGHG_REG_TIME_INACT         0x26    /* Inactivity time (R/W) */
#define ACCEL_HIGHG_REG_ACT_INACT_CTL      0x27    /* Activity/Inactivity control (R/W) */
#define ACCEL_HIGHG_REG_SHOCK_AXES         0x2A    /* Shock axes control (R/W) */
#define ACCEL_HIGHG_REG_ACT_SHOCK_STATUS   0x2B    /* Shock status (R) */
#define ACCEL_HIGHG_REG_BW_RATE            0x2C    /* Data rate and power mode (R/W) */
#define ACCEL_HIGHG_REG_POWER_CTL          0x2D    /* Power control (R/W) */
#define ACCEL_HIGHG_REG_INT_ENABLE         0x2E    /* Interrupt enable (R/W) */
#define ACCEL_HIGHG_REG_INT_MAP            0x2F    /* Interrupt mapping (R/W) */
#define ACCEL_HIGHG_REG_INT_SOURCE         0x30    /* Interrupt source (R) */
#define ACCEL_HIGHG_REG_DATA_FORMAT        0x31    /* Data format control (R/W) */
#define ACCEL_HIGHG_REG_DATAX0             0x32    /* X-Axis Data 0 (R) */
#define ACCEL_HIGHG_REG_DATAX1             0x33    /* X-Axis Data 1 (R) */
#define ACCEL_HIGHG_REG_DATAY0             0x34    /* Y-Axis Data 0 (R) */
#define ACCEL_HIGHG_REG_DATAY1             0x35    /* Y-Axis Data 1 (R) */
#define ACCEL_HIGHG_REG_DATAZ0             0x36    /* Z-Axis Data 0 (R) */
#define ACCEL_HIGHG_REG_DATAZ1             0x37    /* Z-Axis Data 1 (R) */
#define ACCEL_HIGHG_REG_FIFO_CTL           0x38    /* FIFO control (R/W) */
#define ACCEL_HIGHG_REG_FIFO_STATUS        0x39    /* FIFO status (R) */

struct accel_highg_data {
	int16_t accel_x, accel_y, accel_z;
	uint8_t status;
};

int accel_highg_init(void);
int accel_highg_read(struct accel_highg_data *data);
int accel_highg_set_range(uint8_t range);
int accel_highg_set_threshold(uint16_t threshold);

#endif /* ACCEL_HIGHG_H */
