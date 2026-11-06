#include "nrf.h"
#include "ble_price_service.h"
#include "eink_driver.h"
#include "nrf_pwr_mgmt.h"

int main(void) {
    // Init BLE
    ble_stack_init();
    gap_params_init();
    gatt_init();
    advertising_init();
    services_init();
    conn_params_init();

    // Init E-Ink
    eink_init();
    eink_clear();
    eink_print("READY");

    advertising_start();
    nrf_pwr_mgmt_init();

    while (1) {
        idle_state_handle();
    }
}
