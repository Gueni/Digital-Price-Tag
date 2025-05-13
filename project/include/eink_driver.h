#include "eink_driver.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include <string.h>

#define EINK_DC_PIN   17
#define EINK_RST_PIN  18
#define EINK_CS_PIN   19

void eink_spi_send(uint8_t data) {
    // Placeholder SPI send
}

void eink_command(uint8_t cmd) {
    nrf_gpio_pin_clear(EINK_DC_PIN);
    eink_spi_send(cmd);
}

void eink_data(uint8_t data) {
    nrf_gpio_pin_set(EINK_DC_PIN);
    eink_spi_send(data);
}

void eink_init() {
    nrf_gpio_cfg_output(EINK_DC_PIN);
    nrf_gpio_cfg_output(EINK_RST_PIN);
    nrf_gpio_cfg_output(EINK_CS_PIN);

    nrf_gpio_pin_clear(EINK_RST_PIN);
    nrf_delay_ms(200);
    nrf_gpio_pin_set(EINK_RST_PIN);
    nrf_delay_ms(200);

    eink_command(0x01); // Power settings
    eink_data(0x03);
}

void eink_clear() {
    eink_command(0x10);
    for (int i = 0; i < 2500; i++) eink_data(0xFF);
    eink_refresh();
}

void eink_print(const char* text) {
    // Dummy: Assume mapped text to pixels and send
    eink_clear();
    eink_command(0x13);
    for (size_t i = 0; i < strlen(text); i++) eink_data(text[i]);
    eink_refresh();
}

void eink_refresh() {
    eink_command(0x12);
    nrf_delay_ms(100);
}
