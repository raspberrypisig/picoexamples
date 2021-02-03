#include "main.h"

/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// Output PWM signals on pins 0 and 1

#include "pico/stdlib.h"
#include "hardware/pwm.h"

#include "hardware/pll.h"
#include "hardware/clocks.h"
#include "hardware/structs/pll.h"
#include "hardware/structs/clocks.h"

int main() {
    ///tag::setup_pwm[]

    // Tell GPIO 2 and 3 they are allocated to the PWM
    gpio_set_function(2, GPIO_FUNC_PWM);
    gpio_set_function(3, GPIO_FUNC_PWM);

    // Find out which PWM slice is connected to GPIO 1 
    uint slice_num = pwm_gpio_to_slice_num(1);

    // Set period of 4 cycles (0 to 3 inclusive)
    pwm_set_wrap(slice_num, 3);
    // Set channel A output high for one cycle before dropping
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 1);
    // Set initial B output high for three cycles before dropping
    pwm_set_chan_level(slice_num, PWM_CHAN_B, 3);

    // Change clk_sys to be 48MHz. The simplest way is to take this from PLL_USB
    // which has a source frequency of 48MHz
#if 0
    clock_configure(clk_sys,
                    CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX,
                    CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB,
                    48 * MHZ,
                    48 * MHZ);
#endif 

    pwm_set_clkdiv(slice_num, 1.f);

    // Set the PWM running
    pwm_set_enabled(slice_num, true);
    ///end::setup_pwm[]

    // Note we could also use pwm_set_gpio_level(gpio, x) which looks up the
    // correct slice and channel for a given GPIO.

    while (1) {
        tight_loop_contents();
    }
}


/*
int main() {
    while (1) {
        tight_loop_contents();
    }
}
*/

