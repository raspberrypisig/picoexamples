#include "main.h"

void tud_cdc_rx_wanted_cb(uint8_t itf, char wanted_char) { 
  reset_usb_boot(0, 0); 
} // go to flash mode

int main() {
    stdio_init_all();
    tud_cdc_set_wanted_char('\0');
    sleep_ms(2000);
    printf("Starting program...\n");
    
    while (true) {
        printf("Hello, world!\n");
        sleep_ms(5000);
    }
    return 0;
}

