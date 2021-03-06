// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// ----- //
// hello //
// ----- //

#define hello_wrap_target 0
#define hello_wrap 3

static const uint16_t hello_program_instructions[] = {
            //     .wrap_target
    0x80a0, //  0: pull   block                      
    0xa027, //  1: mov    x, osr                     
    0xa0c1, //  2: mov    isr, x                     
    0x8020, //  3: push   block                      
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program hello_program = {
    .instructions = hello_program_instructions,
    .length = 4,
    .origin = -1,
};

static inline pio_sm_config hello_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + hello_wrap_target, offset + hello_wrap);
    return c;
}

static inline void hello_program_init(PIO pio, uint sm, uint offset, uint pin) {
    pio_sm_config c = hello_program_get_default_config(offset);
    // Load our configuration, and jump to the start of the program
    pio_sm_init(pio, sm, offset, &c);
    // Set the state machine running
    pio_sm_set_enabled(pio, sm, true);
}

#endif
