// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// ---------- //
// countedges //
// ---------- //

#define countedges_wrap_target 0
#define countedges_wrap 5

static const uint16_t countedges_program_instructions[] = {
            //     .wrap_target
    0xa02b, //  0: mov    x, !null                   
    0x00c3, //  1: jmp    pin, 3                     
    0x0001, //  2: jmp    1                          
    0xe053, //  3: set    y, 19                      
    0xa0c2, //  4: mov    isr, y                     
    0x8020, //  5: push   block                      
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program countedges_program = {
    .instructions = countedges_program_instructions,
    .length = 6,
    .origin = -1,
};

static inline pio_sm_config countedges_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + countedges_wrap_target, offset + countedges_wrap);
    return c;
}

static inline void countedges_program_init(PIO pio, uint sm, uint offset, uint in_pin, uint jmp_pin) {
    pio_sm_config c = countedges_program_get_default_config(offset);
    sm_config_set_in_pins(&c, in_pin);
    sm_config_set_jmp_pin(&c, jmp_pin);
    // Load our configuration, and jump to the start of the program
    pio_sm_init(pio, sm, offset, &c);
    // Set the state machine running
    //pio_sm_set_enabled(pio, sm, true);
}

#endif

// -------------- //
// referencetimer //
// -------------- //

#define referencetimer_wrap_target 0
#define referencetimer_wrap 5

static const uint16_t referencetimer_program_instructions[] = {
            //     .wrap_target
    0x80a0, //  0: pull   block                      
    0xa027, //  1: mov    x, osr                     
    0xe001, //  2: set    pins, 1                    
    0x0043, //  3: jmp    x--, 3                     
    0xe001, //  4: set    pins, 1                    
    0x0005, //  5: jmp    5                          
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program referencetimer_program = {
    .instructions = referencetimer_program_instructions,
    .length = 6,
    .origin = -1,
};

static inline pio_sm_config referencetimer_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + referencetimer_wrap_target, offset + referencetimer_wrap);
    return c;
}

static inline void referencetimer_program_init(PIO pio, uint sm, uint offset, uint in_pin, uint set_pin) {
       pio_sm_set_consecutive_pindirs(pio, sm, set_pin, 1, true);
    pio_sm_config c = referencetimer_program_get_default_config(offset);
    //sm_config_set_out_shift(&c, false, true, 32);
    //pio_sm_set_consecutive_pindirs(pio, sm, set_pin, 1, true);
    //sm_config_set_in_pins(&c, in_pin);
    sm_config_set_set_pins(&c, set_pin, 1);
    pio_sm_init(pio, sm, offset, &c);
}

#endif

