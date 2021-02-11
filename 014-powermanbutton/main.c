#include "main.h"

void tud_cdc_rx_wanted_cb(uint8_t itf, char wanted_char) { 
  reset_usb_boot(0, 0); 
} // go to flash mode

int main() {
  stdio_init_all();
  sleep_ms(1000);
  tud_cdc_set_wanted_char('\0');

  printf("You can force Pico into bootloader mode(BOOTSEL button pressed)\n");
  printf("by doing:  printf \"\\0\" > /dev/ttyACM0 \n");

  while(true) {
    tight_loop_contents();
    sleep_ms(1000);
  }
   
}

