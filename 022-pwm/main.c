#include "main.h"

#define SQUAREWAVE_PIN 20 // slice 2, channel A

void tud_cdc_rx_wanted_cb(uint8_t itf, char wanted_char) { 
  reset_usb_boot(0, 0); 
} // go to flash mode

int main() {
  stdio_init_all();
  sleep_ms(1000);
  tud_cdc_set_wanted_char('\0');

  //const double freq  = 50.2; 
	const float freq  = 50.8; 

	gpio_set_function(SQUAREWAVE_PIN, GPIO_FUNC_PWM); 
	uint slice_num = pwm_gpio_to_slice_num(SQUAREWAVE_PIN); 

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

  while(true) {
    tight_loop_contents();
  }
   
}














	

