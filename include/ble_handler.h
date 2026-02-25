#ifndef BLE_HANDLER_H
#define BLE_HANDLER_H

#include <stdint.h>
#include "sensor_manager.h"

int ble_handler_init(void);
int ble_start_advertising(void);
void ble_send_sensor_data(uint8_t *data, uint16_t len);

/* Sensor-specific notification functions */
void ble_notify_imu(const struct sensor_data *data);
void ble_notify_highg(const struct sensor_data *data);
void ble_notify_cap(const struct sensor_data *data);
void ble_notify_adc(const struct sensor_data *data);

#endif /* BLE_HANDLER_H */
