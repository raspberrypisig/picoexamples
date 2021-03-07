/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "main.h"
#include "blink.pio.h"

void tud_cdc_rx_wanted_cb(uint8_t itf, char wanted_char) { 
  reset_usb_boot(0, 0); 
} // go to flash mode

void blink_pin_forever(PIO pio, uint sm, uint offset, uint pin, uint freq);

int main() {
 stdio_init_all();
  sleep_ms(1000);
  tud_cdc_set_wanted_char('\0');

    // todo get free sm
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &blink_program);
    printf("Loaded program at %d\n", offset);

    blink_pin_forever(pio, 0, offset, 0, 3);
    blink_pin_forever(pio, 1, offset, 6, 4);
    blink_pin_forever(pio, 2, offset, 11, 1);
}

void blink_pin_forever(PIO pio, uint sm, uint offset, uint pin, uint freq) {
    blink_program_init(pio, sm, offset, pin);
    pio_sm_set_enabled(pio, sm, true);

    printf("Blinking pin %d at freq %d\n", pin, freq);
    pio->txf[sm] = 24000000 / freq;
}
