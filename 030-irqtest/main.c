#include "main.h"

#define MEASURE_PIN 3
#define TEST_SQUAREWAVE_PIN 20 // PWM slice 2, channel A

//Jumper GPIO 14 and 15
#define STATEMACHINE0_JMP_PIN 14
#define STATEMACHINE1_SET_PIN 15

#define STATEMACHINE0_IN_PIN MEASURE_PIN
#define STATEMACHINE1_IN_PIN MEASURE_PIN


//#define DEBUG 1

void tud_cdc_rx_wanted_cb(uint8_t itf, char wanted_char) { 
  reset_usb_boot(0, 0); 
} // go to flash mode



void captureSample(PIO pio, uint sm0, uint sm1, uint offset1, uint offset2) {
 pio_sm_clear_fifos(pio, sm0);
 pio_sm_clear_fifos(pio, sm1);
 sleep_ms(50);
  pio_enable_sm_mask_in_sync(pio, 3);
  //pio_restart_sm_mask(pio,3);
  //pio_clkdiv_restart_sm_mask();

  //sleep_ms(3000);
  uint32_t twentyone = pio_sm_get_blocking(pio, sm0);
  printf("Expect twentyone: %u\n", twentyone);
}

int main() {
  stdio_init_all();
  sleep_ms(1000);
  tud_cdc_set_wanted_char('\0');
  
  PIO pio = pio0;
    
  uint offset1 = pio_add_program(pio, &waitforirq_program);
  uint offset2 = pio_add_program(pio, &raiseirq_program);

  uint sm0 = 0;
  uint sm1 = 1;

  pio_sm_claim(pio, sm0);
  pio_sm_claim(pio, sm1);

  waitforirq_program_init(pio, sm0, offset1);
  raiseirq_program_init(pio, sm1, offset2);

  float freqcounter;

  //while(true) {
  captureSample(pio, sm0, sm1, offset1, offset2);
  //}
   
}
