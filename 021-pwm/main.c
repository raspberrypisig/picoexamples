
#include "main.h"

#define SQUAREWAVE_PIN 20 // slice 2, channel A

void tud_cdc_rx_wanted_cb(uint8_t itf, char wanted_char) { 
  reset_usb_boot(0, 0); 
} // go to flash mode

void calculatePrescalerAndWrap(float freq) {
  float divider  = 1.f;
  uint16_t wrap = 0;
   
  if (freq > 180000) {
    divider = 2.f*(48000000/freq);
    wrap = 2;
    return;
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
    return;
  }
    
 wrap = (48000000/divider) / freq; 
  
  // Set up the flexible divider/compare
  /*
  uint16_t divider  = 1;
  uint16_t compare = 0;
  tc_clock_prescaler prescaler = TC_CLOCK_PRESCALER_DIV1;

  if ((freq < 24000000) && (freq > 800)) {
    divider = 1;
    prescaler = TC_CLOCK_PRESCALER_DIV1;
    compare = 48000000/freq;
  } else if (freq > 400) {
    divider = 2;
    prescaler = TC_CLOCK_PRESCALER_DIV2;
    compare = (48000000/2)/freq;
  } else if (freq > 200) {
    divider = 4;
    prescaler = TC_CLOCK_PRESCALER_DIV4;
    compare = (48000000/4)/freq;
  } else if (freq > 100) {
    divider = 8;
    prescaler = TC_CLOCK_PRESCALER_DIV8;
    compare = (48000000/8)/freq;
  } else if (freq > 50) {
    divider = 16;
    prescaler = TC_CLOCK_PRESCALER_DIV16;
    compare = (48000000/16)/freq;
  } else if (freq > 12) {
    divider = 64;
    prescaler = TC_CLOCK_PRESCALER_DIV64;
    compare = (48000000/64)/freq;
  } else if (freq > 3) {
    divider = 256;
    prescaler = TC_CLOCK_PRESCALER_DIV256;
    compare = (48000000/256)/freq;
  } else if (freq >= 0.75) {
    divider = 1024;
    prescaler = TC_CLOCK_PRESCALER_DIV1024;
    compare = (48000000/1024)/freq;
  } else {
    Serial.println("Invalid frequency");
    while (1) delay(10);
  }
  */
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
