#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(fitbeat_app);

#include "sensor_manager.h"
#include "ble_handler.h"

int main(void)
{
	LOG_INF("Fitbeat firmware starting...");

	/* Initialize Bluetooth */
	int err = bt_enable(NULL);
	if (err) {
		LOG_ERR("Bluetooth init failed (err %d)", err);
		return err;
	}
	LOG_INF("Bluetooth initialized");

	/* Initialize sensors */
	err = sensor_manager_init();
	if (err) {
		LOG_ERR("Sensor manager init failed (err %d)", err);
		return err;
	}
	LOG_INF("Sensors initialized");

	/* Initialize BLE handler */
	err = ble_handler_init();
	if (err) {
		LOG_ERR("BLE handler init failed (err %d)", err);
		return err;
	}
	LOG_INF("BLE handler initialized");

	/* Start advertising */
	err = ble_start_advertising();
	if (err) {
		LOG_ERR("Failed to start advertising (err %d)", err);
		return err;
	}
	LOG_INF("BLE advertising started");

	/* Sensor reading loop */
	while (1) {
		sensor_manager_read();
		k_sleep(K_MSEC(100)); // 10 Hz sampling rate
	}

	return 0;
}
