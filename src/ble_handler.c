#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/logging/log.h>
#include <string.h>

LOG_MODULE_REGISTER(ble_handler);

#include "ble_handler.h"
#include "sensor_manager.h"

/* Custom Service UUIDs */
#define BT_UUID_FITBEAT_SERVICE \
	BT_UUID_128_ENCODE(0x12345678, 0x9abc, 0xdef0, 0x1234, 0x56789abcdef0)

#define BT_UUID_FITBEAT_IMU_CHAR \
	BT_UUID_128_ENCODE(0x87654321, 0xcba9, 0x0fed, 0x4321, 0x0fedcba98765)

#define BT_UUID_FITBEAT_HIGHG_CHAR \
	BT_UUID_128_ENCODE(0xaaaaaaaa, 0xbbbb, 0xcccc, 0xdddd, 0xeeeeeeeeeeee)

#define BT_UUID_FITBEAT_CAP_CHAR \
	BT_UUID_128_ENCODE(0xffffffff, 0x1111, 0x2222, 0x3333, 0x444444444444)

#define BT_UUID_FITBEAT_ADC_CHAR \
	BT_UUID_128_ENCODE(0x55555555, 0x6666, 0x7777, 0x8888, 0x999999999999)

static struct bt_uuid_128 fitbeat_svc_uuid = BT_UUID_INIT_128(BT_UUID_FITBEAT_SERVICE);
static struct bt_uuid_128 imu_char_uuid = BT_UUID_INIT_128(BT_UUID_FITBEAT_IMU_CHAR);
static struct bt_uuid_128 highg_char_uuid = BT_UUID_INIT_128(BT_UUID_FITBEAT_HIGHG_CHAR);
static struct bt_uuid_128 cap_char_uuid = BT_UUID_INIT_128(BT_UUID_FITBEAT_CAP_CHAR);
static struct bt_uuid_128 adc_char_uuid = BT_UUID_INIT_128(BT_UUID_FITBEAT_ADC_CHAR);

/* Notification enabled flags */
static uint8_t imu_notify_enabled = 0;
static uint8_t highg_notify_enabled = 0;
static uint8_t cap_notify_enabled = 0;
static uint8_t adc_notify_enabled = 0;

/* GATT Characteristic callback for IMU CCC */
static void imu_ccc_changed(const struct bt_gatt_attr *attr, uint16_t value)
{
	imu_notify_enabled = (value == BT_GATT_CCC_NOTIFY);
	LOG_INF("IMU notifications %s", imu_notify_enabled ? "enabled" : "disabled");
}

/* GATT Characteristic callback for High-G CCC */
static void highg_ccc_changed(const struct bt_gatt_attr *attr, uint16_t value)
{
	highg_notify_enabled = (value == BT_GATT_CCC_NOTIFY);
	LOG_INF("High-G notifications %s", highg_notify_enabled ? "enabled" : "disabled");
}

/* GATT Characteristic callback for Capacitive CCC */
static void cap_ccc_changed(const struct bt_gatt_attr *attr, uint16_t value)
{
	cap_notify_enabled = (value == BT_GATT_CCC_NOTIFY);
	LOG_INF("Capacitive sensor notifications %s", cap_notify_enabled ? "enabled" : "disabled");
}

/* GATT Characteristic callback for ADC CCC */
static void adc_ccc_changed(const struct bt_gatt_attr *attr, uint16_t value)
{
	adc_notify_enabled = (value == BT_GATT_CCC_NOTIFY);
	LOG_INF("ADC notifications %s", adc_notify_enabled ? "enabled" : "disabled");
}

/* GATT Service and Characteristics Definition */
static struct bt_gatt_attr fitbeat_attrs[] = {
	/* Service Declaration */
	BT_GATT_PRIMARY_SERVICE(&fitbeat_svc_uuid),

	/* IMU Characteristic */
	BT_GATT_CHARACTERISTIC(&imu_char_uuid,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ,
			       NULL, NULL, NULL),
	BT_GATT_CCC(imu_ccc_changed,
		     BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),

	/* High-G Accelerometer Characteristic */
	BT_GATT_CHARACTERISTIC(&highg_char_uuid,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ,
			       NULL, NULL, NULL),
	BT_GATT_CCC(highg_ccc_changed,
		     BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),

	/* Capacitive Sensor Characteristic */
	BT_GATT_CHARACTERISTIC(&cap_char_uuid,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ,
			       NULL, NULL, NULL),
	BT_GATT_CCC(cap_ccc_changed,
		     BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),

	/* ADC Characteristic */
	BT_GATT_CHARACTERISTIC(&adc_char_uuid,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ,
			       NULL, NULL, NULL),
	BT_GATT_CCC(adc_ccc_changed,
		     BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
};

static struct bt_gatt_service fitbeat_svc = BT_GATT_SERVICE(fitbeat_attrs);

/* BLE advertisement setup */
static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA_BYTES(BT_DATA_UUID128_ALL,
		      0xf0, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12,
		      0x34, 0x12, 0xf0, 0xde, 0xbc, 0x9a, 0x78, 0x56),
};

/* Connection callback */
static void connected(struct bt_conn *conn, uint8_t err)
{
	if (err) {
		LOG_ERR("Connection failed (err %u)", err);
	} else {
		LOG_INF("Connected");
	}
}

/* Disconnection callback */
static void disconnected(struct bt_conn *conn, uint8_t reason)
{
	LOG_INF("Disconnected (reason %u)", reason);
	imu_notify_enabled = 0;
	highg_notify_enabled = 0;
	cap_notify_enabled = 0;
	adc_notify_enabled = 0;
}

static struct bt_conn_cb conn_callbacks = {
	.connected = connected,
	.disconnected = disconnected,
};

int ble_handler_init(void)
{
	LOG_INF("Initializing BLE handler...");

	bt_conn_cb_register(&conn_callbacks);
	bt_gatt_service_register(&fitbeat_svc);

	return 0;
}

int ble_start_advertising(void)
{
	int err;

	err = bt_le_adv_start(BT_LE_ADV_CONN_NAME, ad, ARRAY_SIZE(ad), NULL, 0);
	if (err) {
		LOG_ERR("Advertising failed to start (err %d)", err);
		return err;
	}

	return 0;
}

void ble_send_sensor_data(uint8_t *data, uint16_t len)
{
	/* This is a generic function for sending arbitrary data */
	/* For sensor streaming, use the specific characteristic notification functions below */
	
	/* IMU: 6 floats (accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z) = 24 bytes */
	if (imu_notify_enabled && len >= 24) {
		bt_gatt_notify(NULL, &fitbeat_attrs[2], data, len);
	}
}

/* Send IMU data notification */
void ble_notify_imu(const struct sensor_data *data)
{
	if (!imu_notify_enabled) {
		return;
	}

	struct {
		float accel[3];
		float gyro[3];
	} imu_payload = {
		.accel[0] = data->imu.accel_x,
		.accel[1] = data->imu.accel_y,
		.accel[2] = data->imu.accel_z,
		.gyro[0] = data->imu.gyro_x,
		.gyro[1] = data->imu.gyro_y,
		.gyro[2] = data->imu.gyro_z,
	};

	bt_gatt_notify(NULL, &fitbeat_attrs[2], (uint8_t *)&imu_payload, sizeof(imu_payload));
}

/* Send High-G data notification */
void ble_notify_highg(const struct sensor_data *data)
{
	if (!highg_notify_enabled) {
		return;
	}

	struct {
		float accel[3];
	} highg_payload = {
		.accel[0] = data->highg_accel.accel_x,
		.accel[1] = data->highg_accel.accel_y,
		.accel[2] = data->highg_accel.accel_z,
	};

	bt_gatt_notify(NULL, &fitbeat_attrs[5], (uint8_t *)&highg_payload, sizeof(highg_payload));
}

/* Send Capacitive sensor data notification */
void ble_notify_cap(const struct sensor_data *data)
{
	if (!cap_notify_enabled) {
		return;
	}

	uint16_t cap_payload = data->cap_value;
	bt_gatt_notify(NULL, &fitbeat_attrs[8], (uint8_t *)&cap_payload, sizeof(cap_payload));
}

/* Send ADC data notification */
void ble_notify_adc(const struct sensor_data *data)
{
	if (!adc_notify_enabled) {
		return;
	}

	struct {
		uint16_t ch[3];
	} adc_payload = {
		.ch[0] = data->adc_ch0,
		.ch[1] = data->adc_ch1,
		.ch[2] = data->adc_ch2,
	};

	bt_gatt_notify(NULL, &fitbeat_attrs[11], (uint8_t *)&adc_payload, sizeof(adc_payload));
}

