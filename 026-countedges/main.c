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
  sleep_ms(10000);
  tud_cdc_set_wanted_char('\0');
  
  float freq = 50.8f;
  createSquareWave(freq);

  PIO pio = pio0;
  uint offset = pio_add_program(pio, &countedges_program);
  //printf("Program offset at: %d\n", offset);

  uint32_t REFERENCE_FREQ = 125000000;
    
  uint offset1 = pio_add_program(pio, &countedges_program);
  //uint offset2 = pio_add_program(pio, &referencetimer_program);

  uint sm0 = 0;
  uint sm1 = 1;

  pio_sm_claim(pio, sm0);
  pio_sm_claim(pio, sm1);

  countedges_program_init(pio, sm0, offset, MEASURE_PIN);
  sleep_ms(1000);
  pio_sm_exec_wait_blocking(pio, sm0, pio_encode_mov_not(pio_isr, pio_x));
  pio_sm_exec_wait_blocking(pio, sm0, pio_encode_push(false, false));
  uint32_t num = pio_sm_get_blocking(pio, sm0);

  printf("Num: %u\n", num);

  while(true) {
    tight_loop_contents();
  }
   
}
