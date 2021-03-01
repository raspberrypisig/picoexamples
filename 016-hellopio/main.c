#include "main.h"

void tud_cdc_rx_wanted_cb(uint8_t itf, char wanted_char) { 
  reset_usb_boot(0, 0); 
} // go to flash mode

int main() {
  stdio_init_all();
  sleep_ms(10000);
  tud_cdc_set_wanted_char('\0');
  
  PIO pio = pio0;
  uint offset = pio_add_program(pio, &hello_program);
  printf("Program offset at: %d\n", offset);

  uint sm = pio_claim_unused_sm(pio, true);
  hello_program_init(pio, sm, offset, PICO_DEFAULT_LED_PIN);

  uint32_t num = pio_sm_get_blocking(pio, sm);
  printf("The meaning of life: %d\n", 0xffffffff - num);



  while(true) {
    tight_loop_contents();
  }
   
}

