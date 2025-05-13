#include "ble_price_service.h"
#include "eink_driver.h"

#define CUSTOM_SERVICE_UUID 0x180C
#define PRICE_CHAR_UUID     0x2A56
#define TRIGGER_CHAR_UUID   0x2A57

static uint16_t service_handle;
static ble_gatts_char_handles_t price_char_handles;
static ble_gatts_char_handles_t trigger_char_handles;

void on_ble_write(ble_evt_t const * p_ble_evt) {
    ble_gatts_evt_write_t const * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

    if (p_evt_write->handle == price_char_handles.value_handle) {
        char value[32] = {0};
        memcpy(value, p_evt_write->data, p_evt_write->len);
        eink_clear();
        eink_print(value);
    }
    if (p_evt_write->handle == trigger_char_handles.value_handle) {
        eink_refresh();
    }
}

void services_init(void) {
    ble_uuid_t service_uuid = {.uuid = CUSTOM_SERVICE_UUID, .type = BLE_UUID_TYPE_BLE};
    sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &service_uuid, &service_handle);

    ble_gatts_char_md_t char_md = {.char_props = {.write = 1, .write_wo_resp = 1}};
    ble_uuid_t char_uuid = {.uuid = PRICE_CHAR_UUID, .type = BLE_UUID_TYPE_BLE};
    ble_gatts_attr_md_t attr_md = {.vloc = BLE_GATTS_VLOC_STACK};
    ble_gatts_attr_t attr_char_value = {.p_uuid = &char_uuid, .p_attr_md = &attr_md, .init_len = 32, .max_len = 32};

    sd_ble_gatts_characteristic_add(service_handle, &char_md, &attr_char_value, &price_char_handles);

    char_uuid.uuid = TRIGGER_CHAR_UUID;
    sd_ble_gatts_characteristic_add(service_handle, &char_md, &attr_char_value, &trigger_char_handles);
}
