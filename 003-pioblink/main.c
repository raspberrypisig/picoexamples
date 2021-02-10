#include "main.h"

void tud_cdc_rx_wanted_cb(uint8_t itf, char wanted_char) { 
  reset_usb_boot(0, 0); 
} // go to flash mode

const uint LED_PIN = 25;

int main() {
    stdio_init_all();
    sleep_ms(10000);
    tud_cdc_set_wanted_char('\0');
    //bi_decl(bi_program_description("First Blink"));
    //bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (1) {
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
        gpio_put(LED_PIN, 1);
        sleep_ms(1000);
    }
}