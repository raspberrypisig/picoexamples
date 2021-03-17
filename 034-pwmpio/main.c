#include "main.h"

#define SM0_SET_PIN 15

//#define DEBUG 1

void tud_cdc_rx_wanted_cb(uint8_t itf, char wanted_char) { 
  reset_usb_boot(0, 0); 
} // go to flash mode

int main() {
  stdio_init_all();
  sleep_ms(1000);
  tud_cdc_set_wanted_char('\0');
  
  PIO pio = pio0;
  

    
  uint offset1 = pio_add_program(pio, &halfmeg_program);

  uint sm0 = 0;

  pio_sm_claim(pio, sm0);

  halfmeg_program_init(pio, sm0, offset1, SM0_SET_PIN);
  

  while(true) {
    tight_loop_contents();
  }
   
}
