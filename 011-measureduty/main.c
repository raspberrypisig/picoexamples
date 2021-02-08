#include "main.h"

// This example drives a PWM output at a range of duty cycles, and uses
// another PWM slice in input mode to measure the duty cycle. You'll need to
// connect these two pins with a jumper wire:
const uint OUTPUT_PIN = 2;
const uint MEASURE_PIN = 5;

float measure_duty_cycle(uint gpio) {
    // Only the PWM B pins can be used as inputs.
    assert(pwm_gpio_to_channel(gpio) == PWM_CHAN_B);
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    printf("Slice number: %d\n", slice_num);

    // Count once for every 100 cycles the PWM B input is high
    pwm_config cfg = pwm_get_default_config();
    pwm_config_set_clkdiv_mode(&cfg, PWM_DIV_B_HIGH);
    pwm_config_set_clkdiv(&cfg, 100);
    pwm_init(slice_num, &cfg, false);
    gpio_set_function(gpio, GPIO_FUNC_PWM);

    pwm_set_enabled(slice_num, true);
    sleep_ms(10);
    pwm_set_enabled(slice_num, false);
    float counting_rate = clock_get_hz(clk_sys) / 100;
    float max_possible_count = counting_rate * 0.01;
    return pwm_get_counter(slice_num) / max_possible_count;
}

const float test_duty_cycles[] = {
        0.f,
        0.1f,
        0.5f,
        0.9f,
        1.f
};

int main() {
  stdio_init_all();

  //gpio_init(OUTPUT_PIN);
  //gpio_set_dir(OUTPUT_PIN, GPIO_OUT);
  //gpio_put(OUTPUT_PIN, 1);

  gpio_set_function(OUTPUT_PIN, GPIO_FUNC_PWM);
  
  // PWM Slice (ie. PWM number between 0-7)
  uint slice_num = pwm_gpio_to_slice_num(OUTPUT_PIN);

  
  // Set period of 4 cycles (0 to 3 inclusive)
  pwm_set_wrap(slice_num, 3);
  // Set channel A output high for one cycle before dropping(25% duty cycle)
  pwm_set_chan_level(slice_num, PWM_CHAN_A, 1);
  // Set the PWM running
  pwm_set_enabled(slice_num, true);

  while(true) {
        float measured_duty_cycle = measure_duty_cycle(MEASURE_PIN);
        printf("Measured input duty cycle = %.1f%%\n",
               measured_duty_cycle * 100.f);
               sleep_ms(10000);
  }
   
}

