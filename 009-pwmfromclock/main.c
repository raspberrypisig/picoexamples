#include "main.h"

int main() {

    // GPIO 21 is pin 27 on Pico

    clock_gpio_init(21, CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_USB, 4800);

    while(true) {
        tight_loop_contents();
    }

}

