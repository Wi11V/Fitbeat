#ifndef BLE_HANDLER_H
#define BLE_HANDLER_H

#include <stdint.h>

int ble_handler_init(void);
int ble_start_advertising(void);
void ble_send_sensor_data(uint8_t *data, uint16_t len);

#endif /* BLE_HANDLER_H */
