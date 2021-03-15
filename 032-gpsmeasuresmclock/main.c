#include "main.h"

#define GPS_PIN 3
//Jumper GPIO 14 & 15
#define SM0_JMP_PIN 14 
#define SM1_SET_PIN 15

//#define DEBUG 1

void tud_cdc_rx_wanted_cb(uint8_t itf, char wanted_char) { 
  reset_usb_boot(0, 0); 
} // go to flash mode


void captureSample(PIO pio, uint sm0, uint sm1, uint offset1, uint offset2) {
   uint32_t REFERENCE_FREQ = 125000000UL;
   pio_sm_clear_fifos(pio, sm0);
   pio_sm_clear_fifos(pio, sm1);
   pio_enable_sm_mask_in_sync(pio, 3);
   uint32_t countedges = pio_sm_get_blocking(pio, sm0);
   printf("Count edges: %u\n", countedges);
}

int main() {
  stdio_init_all();
  sleep_ms(1000);
  tud_cdc_set_wanted_char('\0');
  
  PIO pio = pio0;
  

    
  uint offset1 = pio_add_program(pio, &countedges_program);
  uint offset2 = pio_add_program(pio, &gate_program);

  uint sm0 = 0;
  uint sm1 = 1;

  pio_sm_claim(pio, sm0);
  pio_sm_claim(pio, sm1);

  countedges_program_init(pio, sm0, offset1, SM0_JMP_PIN);
  gate_program_init(pio, sm1, offset2, GPS_PIN, SM1_SET_PIN);

  //float freqcounter;

  //while(true) {
    captureSample(pio, sm0, sm1, offset1, offset2);

  //}
   
}
