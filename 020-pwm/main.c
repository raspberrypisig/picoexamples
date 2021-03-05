
#include "main.h"

#define SQUAREWAVE_PIN 20 // slice 2, channel A

void tud_cdc_rx_wanted_cb(uint8_t itf, char wanted_char) { 
  reset_usb_boot(0, 0); 
} // go to flash mode

void createSquareWave(float freq) {
    gpio_set_function(SQUAREWAVE_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(SQUAREWAVE_PIN);
    pwm_set_clkdiv(slice_num, 16.f);
    uint16_t wrap = (uint16_t) ((48000000/16) / freq);
    pwm_set_wrap(slice_num, wrap - 1 );
    pwm_set_chan_level(slice_num, PWM_CHAN_A, (wrap - 1)/2);
    pwm_set_enabled(slice_num, true);
}

int main() {
    stdio_init_all();
    tud_cdc_set_wanted_char('\0');
    sleep_ms(2000);
    printf("Starting program...\n");
    
    float freq = 50.8;
  
    createSquareWave(freq);  
  
    while(true) {
      tight_loop_contents();
    }
  
    return 0;
}
