#include "main.h"

#define MEASURE_PIN 3
#define TEST_SQUAREWAVE_PIN 20 // PWM slice 2, channel A

//Jumper GPIO 14 and 15
#define STATEMACHINE0_JMP_PIN 14
#define STATEMACHINE1_SET_PIN 15

#define STATEMACHINE0_IN_PIN MEASURE_PIN
#define STATEMACHINE1_IN_PIN MEASURE_PIN


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

int main() {
  stdio_init_all();
  sleep_ms(1000);
  tud_cdc_set_wanted_char('\0');
  
  float freq = 50.2f;
  //float freq = 50.8f;
  createSquareWave(freq);

  PIO pio = pio0;
  
  uint32_t REFERENCE_FREQ = 125000000;
    
  uint offset1 = pio_add_program(pio, &countedges_program);
  uint offset2 = pio_add_program(pio, &referencetimer_program);

  uint sm0 = 0;
  uint sm1 = 1;

  pio_sm_claim(pio, sm0);
  pio_sm_claim(pio, sm1);

  countedges_program_init(pio, sm0, offset1, STATEMACHINE0_IN_PIN, STATEMACHINE0_JMP_PIN);
  referencetimer_program_init(pio, sm1, offset2, STATEMACHINE1_IN_PIN, STATEMACHINE1_SET_PIN);

  
  pio_sm_put_blocking(pio, sm1, 125000000);
  //pio_sm_set_enabled(pio, sm0, true);
  //pio_sm_set_enabled(pio,sm1,true);
  pio_enable_sm_mask_in_sync(pio, 3);

  //sleep_ms(3000);
  uint32_t countedges = pio_sm_get_blocking(pio, sm0);
  printf("Count edges: %u\n", countedges);
  uint32_t extrapulsesreference = pio_sm_get_blocking(pio, sm1);
  //printf("Extra raw: %d\n", extrapulsesreference);
  uint32_t totalpulsesreference = REFERENCE_FREQ + 2*extrapulsesreference;
  //printf("Extra ref counts: %d\n", totalpulsesreference);
  float freqcounter = (countedges + 1) * ((1.f * REFERENCE_FREQ)/totalpulsesreference);
  printf("Final freq: %f\n", freqcounter);

  while(true) {
    tight_loop_contents();
  }
   
}
