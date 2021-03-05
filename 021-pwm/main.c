
#include "main.h"

typedef struct {
  float divider;
  uint16_t wrap;
} PWMSettings;

#define SQUAREWAVE_PIN 20 // slice 2, channel A

void tud_cdc_rx_wanted_cb(uint8_t itf, char wanted_char) { 
  reset_usb_boot(0, 0); 
} // go to flash mode

PWMSettings calculatePrescalerAndWrap(float freq) {
  float divider  = -1.f;
  uint16_t wrap = 0;
  PWMSettings settings;
   
  if (freq > 180000) {
    divider = 2.f*(48000000/freq);
    wrap = 2;
    settings.divider = divider;
    settings.wrap = wrap;
    return settings;
  }
  
  else if ((freq < 180000) && (freq > 800)) {
    divider = 1.f;
  } else if (freq > 400) {
    divider = 2.f;
  } else if (freq > 200) {
    divider = 4.f;
  } else if (freq > 100) {
    divider = 8.f;
  } else if (freq > 50) {
    divider = 16.f;
  } else if (freq > 12) {
    divider = 64.f;
  } else if (freq > 3) {
    divider = 255.f;
 else {
    settings.divider = -1.f;
    return;
  }
    
 wrap = (48000000/divider) / freq;
 settings.divider = divider;
 settings.wrap = wrap;
 return settings;
  
}

void createSquareWave(float freq) {
    gpio_set_function(SQUAREWAVE_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(SQUAREWAVE_PIN);
    pwm_set_clkdiv(slice_num, 16.f);
    uint16_t wrap = (uint16_t) ((48000000/16) / freq);
    pwm_set_wrap(slice_num, wrap);
    pwm_set_chan_level(slice_num, PWM_CHAN_A, wrap/2);
    pwm_set_enabled(slice_num, true);
}

int main() {
    stdio_init_all();
    tud_cdc_set_wanted_char('\0');
    sleep_ms(2000);
    printf("Starting program...\n");
    
    //float freq = 50.2;
    float freq = 50.8;
  
    createSquareWave(freq);  
  
    while(true) {
      tight_loop_contents();
    }
  
    return 0;
}
