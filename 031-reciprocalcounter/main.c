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

void createSquareWave(float freq) {
  gpio_set_function(TEST_SQUAREWAVE_PIN, GPIO_FUNC_PWM); 
	uint slice_num = pwm_gpio_to_slice_num(TEST_SQUAREWAVE_PIN); 

	// set frequency
	// determine top given Hz - assumes free-running counter rather than phase-correct
	//u32 f_sys = clock_get_hz(clk_sys); // typically 125'000'000 Hz
  uint32_t f_sys = 125000000UL;
	float divider = f_sys / 1000000UL;
	pwm_set_clkdiv(slice_num, divider); 

	uint16_t top = (uint32_t) (1000000UL/freq) -1;
	pwm_set_wrap(slice_num, top);
	uint16_t level = top/2;
	pwm_set_chan_level(slice_num, 0, level); 
	pwm_set_enabled(slice_num, true); 

}

float captureSample(PIO pio, uint sm0, uint sm1, uint offset1, uint offset2) {
   uint32_t REFERENCE_FREQ = 125000000UL;
  //uint32_t REFERENCE_FREQ = 124999225;
  //uint32_t REFERENCE_FREQ = 124952218;
  //uint32_t REFERENCE_FREQ = 124969866;
  //uint32_t REFERENCE_FREQ = 124988030;
  //uint32_t REFERENCE_FREQ = 124943945;
 pio_sm_clear_fifos(pio, sm0);
 pio_sm_clear_fifos(pio, sm1);
  pio_sm_put_blocking(pio, sm1, REFERENCE_FREQ);
  //pio_sm_set_enabled(pio, sm0, true);
  //pio_sm_set_enabled(pio,sm1,true);
  pio_sm_exec(pio, sm0, pio_encode_jmp(offset1));
  pio_sm_exec(pio, sm1, pio_encode_jmp(offset2));
  pio_enable_sm_mask_in_sync(pio, 3);
  //pio_restart_sm_mask(pio,3);
  //pio_clkdiv_restart_sm_mask();

  //sleep_ms(3000);
  uint32_t countedges = pio_sm_get_blocking(pio, sm0);
  printf("Count edges: %u\n", countedges);
  uint32_t extrapulsesreference = pio_sm_get_blocking(pio, sm1);
  pio_enable_sm_mask_in_sync(pio, 0);
  #ifdef DEBUG
  printf("Extra raw: %d\n", extrapulsesreference);
  #endif
  uint32_t totalpulsesreference = REFERENCE_FREQ + 2*extrapulsesreference + 3 ;
  #ifdef DEBUG
  printf("Extra ref counts: %d\n", totalpulsesreference);
  #endif
  float freqcounter = countedges * ((1.f * REFERENCE_FREQ)/totalpulsesreference);
  return freqcounter;
  //printf("Final freq: %f\n", freqcounter);
}

int main() {
  stdio_init_all();
  sleep_ms(1000);
  tud_cdc_set_wanted_char('\0');
  
  //float freq = 50.f;
  //float freq = 50.2f;
  float freq = 50.8f;
  //float freq = 50.97f;
  //float freq = 100000.f;
  //float freq = 2000.7f;
  
  createSquareWave(freq);

  PIO pio = pio0;
  

    
  uint offset1 = pio_add_program(pio, &countedges_program);
  uint offset2 = pio_add_program(pio, &referencetimer_program);

  uint sm0 = 0;
  uint sm1 = 1;

  pio_sm_claim(pio, sm0);
  pio_sm_claim(pio, sm1);

  countedges_program_init(pio, sm0, offset1, STATEMACHINE0_IN_PIN, STATEMACHINE0_JMP_PIN);
  referencetimer_program_init(pio, sm1, offset2, STATEMACHINE1_IN_PIN, STATEMACHINE1_SET_PIN);

  float freqcounter;

  while(true) {
    freqcounter = captureSample(pio, sm0, sm1, offset1, offset2);
    printf("Final freq: %f\n", freqcounter);
    #ifdef DEBUG
    sleep_ms(30000);
    #else
    sleep_ms(3000);
    #endif
  }
   
}
