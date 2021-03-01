#include "main.h"

// This example drives a PWM output at a range of duty cycles, and uses
// another PWM slice in input mode to measure the duty cycle. You'll need to
// connect these two pins with a jumper wire:
const uint OUTPUT_PIN = 2;
const uint MEASURE_PIN = 5;
uint slice_num = 0;

const uint32_t FREQUENCY_MEASUREMENT_SAMPLING_PERIOD = 10; //ms

bool timerOverflow = false;

void tud_cdc_rx_wanted_cb(uint8_t itf, char wanted_char) { 
  reset_usb_boot(0, 0); 
} // go to flash mode

/*
float measure_duty_cycle(uint gpio) {
    // Only the PWM B pins can be used as inputs.
    assert(pwm_gpio_to_channel(gpio) == PWM_CHAN_B);
    uint slice_num = pwm_gpio_to_slice_num(gpio);

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
*/
/*

// in kHz
int16_t measure_frequency(uint gpio) {
    // Only the PWM B pins can be used as inputs.
    assert(pwm_gpio_to_channel(gpio) == PWM_CHAN_B);
    uint slice_num = pwm_gpio_to_slice_num(gpio);

    // Count once for every 100 cycles the PWM B input is high
    pwm_config cfg = pwm_get_default_config();
    pwm_config_set_clkdiv_mode(&cfg, PWM_DIV_B_FALLING);
    pwm_config_set_clkdiv(&cfg, 1.f); //set by default, increment count for each rising edge
    pwm_init(slice_num, &cfg, false);  //false means don't start pwm
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    //pwm_set_irq_enabled(slice_num, false);
    //pwm_set_counter(slice_num, 0);
    printf("Old counter value: %d\n", pwm_get_counter(slice_num));
    pwm_set_enabled(slice_num, true);
    sleep_ms(10);
    
    
    pwm_set_enabled(slice_num, false);
    int16_t freq = pwm_get_counter(slice_num);
    printf("Freq raw timer count: %hi\n", freq);
    return freq;

}

*/

void on_pwm_wrap() {
    timerOverflow = true;
    pwm_clear_irq(slice_num);
}

// Frequency measured in Hz
uint32_t measure_frequency(uint gpio) {
    // Only the PWM B pins can be used as inputs.
    //assert(pwm_gpio_to_channel(gpio) == PWM_CHAN_B);


    // Count once for every 100 cycles the PWM B input is high
    pwm_config cfg = pwm_get_default_config();
    pwm_config_set_clkdiv_mode(&cfg, PWM_DIV_B_RISING);
    pwm_config_set_clkdiv(&cfg, 1.f); //set by default, increment count for each rising edge
    pwm_init(slice_num, &cfg, false);  //false means don't start pwm
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    
    
    pwm_clear_irq(slice_num);
    pwm_set_irq_enabled(slice_num, true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_wrap);
    irq_set_enabled(PWM_IRQ_WRAP, true);

    //pwm_set_wrap(slice_num, 10000);

    pwm_set_counter(slice_num, 0);
    pwm_set_enabled(slice_num, true);
    //sleep_ms(10);
    sleep_ms(1000);
    pwm_set_enabled(slice_num, false);
    
    uint16_t upscaler = 1;

    if (timerOverflow) {
        timerOverflow = false;
        pwm_set_counter(slice_num, 0);
        pwm_set_enabled(slice_num, true);
        sleep_ms(10);        
        pwm_set_enabled(slice_num, false);
        upscaler = 100;
    }
    
    
    uint16_t counter = (uint16_t) pwm_get_counter(slice_num);
    printf("Raw PWM counter: %d\n", counter);
    uint32_t freq = counter * upscaler;
    return freq;

}

const float test_duty_cycles[] = {
        0.f,
        0.1f,
        0.5f,
        0.9f,
        1.f
};

void create_square_wave(uint gpio) {
  gpio_set_function(gpio, GPIO_FUNC_PWM);
  
  // PWM Slice (ie. PWM number between 0-7)
  uint slice_num = pwm_gpio_to_slice_num(gpio);

  pwm_set_clkdiv(slice_num, 125.f);

  // Set period to 10Khz
  pwm_set_wrap(slice_num, 99);
  // Set channel A output 50% duty cycle
  pwm_set_chan_level(slice_num, PWM_CHAN_A, 50);
  // Set the PWM running
  pwm_set_enabled(slice_num, true);
}

int main() {
    stdio_init_all();
    sleep_ms(10000);

    tud_cdc_set_wanted_char('\0');

    // GPIO 21 is pin 27 on Pico
    //clock_gpio_init(21, CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_USB, 4800);

    //create_square_wave(OUTPUT_PIN);

    slice_num = pwm_gpio_to_slice_num(MEASURE_PIN);

    uint32_t measured_frequency;
    
    while(true) {
        measured_frequency =  measure_frequency(MEASURE_PIN);
        
        if (measured_frequency >= 1000) {
            printf("Frequency count: %d Hz, %d kHz (100Hz resolution)\n\n", measured_frequency, measured_frequency / 1000 );
        }
        
        else {
            printf("Frequency count: %d Hz (1 Hz resolution) \n\n", measured_frequency );
        }
        
        sleep_ms(5000); 
    }



}

