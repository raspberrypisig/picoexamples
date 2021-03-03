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
#define hello_wrap 1

static const uint16_t hello_program_instructions[] = {
            //     .wrap_target
    0xa02b, //  0: mov    x, !null                   
    0x0041, //  1: jmp    x--, 1                     
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program hello_program = {
    .instructions = hello_program_instructions,
    .length = 2,
    .origin = -1,
};

static inline pio_sm_config hello_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + hello_wrap_target, offset + hello_wrap);
    return c;
}

static inline void hello_program_init(PIO pio, uint sm, uint offset, uint pin) {
    pio_sm_config c = hello_program_get_default_config(offset);
    // Autopush enabled
    sm_config_set_in_shift(&c, true, true, 32);
    // Load our configuration, and jump to the start of the program
    pio_sm_init(pio, sm, offset, &c);
    // Set the state machine running
    pio_sm_set_enabled(pio, sm, true);
}

#endif
