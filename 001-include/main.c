#include "main.h"

void tud_cdc_rx_wanted_cb(uint8_t itf, char wanted_char) { 
  reset_usb_boot(0, 0); 
} // go to flash mode

int main() {
  stdio_init_all();
  sleep_ms(10000);
  tud_cdc_set_wanted_char('\0');
  
  while(true) {
    tight_loop_contents();
  }
   
}

