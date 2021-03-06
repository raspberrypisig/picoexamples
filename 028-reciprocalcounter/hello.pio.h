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
#define countedges_wrap 6

static const uint16_t countedges_program_instructions[] = {
            //     .wrap_target
    0xa02b, //  0: mov    x, !null                   
    0x2020, //  1: wait   0 pin, 0                   
    0x20a0, //  2: wait   1 pin, 0                   
    0x00c5, //  3: jmp    pin, 5                     
    0x0041, //  4: jmp    x--, 1                     
    0xa0c9, //  5: mov    isr, !x                    
    0x8020, //  6: push   block                      
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program countedges_program = {
    .instructions = countedges_program_instructions,
    .length = 7,
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

#define referencetimer_wrap_target 8
#define referencetimer_wrap 9

static const uint16_t referencetimer_program_instructions[] = {
    0x80a0, //  0: pull   block                      
    0xa027, //  1: mov    x, osr                     
    0x0042, //  2: jmp    x--, 2                     
    0xe001, //  3: set    pins, 1                    
    0xa02b, //  4: mov    x, !null                   
    0x0007, //  5: jmp    7                          
    0x0047, //  6: jmp    x--, 7                     
    0x00c6, //  7: jmp    pin, 6                     
            //     .wrap_target
    0x0049, //  8: jmp    x--, 9                     
    0x00ca, //  9: jmp    pin, 10                    
            //     .wrap
    0xa0c9, // 10: mov    isr, !x                    
    0x8020, // 11: push   block                      
    0xe000, // 12: set    pins, 0                    
    0x000d, // 13: jmp    13                         
};

#if !PICO_NO_HARDWARE
static const struct pio_program referencetimer_program = {
    .instructions = referencetimer_program_instructions,
    .length = 14,
    .origin = -1,
};

static inline pio_sm_config referencetimer_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + referencetimer_wrap_target, offset + referencetimer_wrap);
    return c;
}

static inline void referencetimer_program_init(PIO pio, uint sm, uint offset, uint in_pin, uint set_pin) {
    pio_gpio_init(pio, set_pin);
    pio_sm_set_consecutive_pindirs(pio, sm, set_pin, 1, true);
    pio_sm_config c = referencetimer_program_get_default_config(offset);
    //sm_config_set_out_shift(&c, false, true, 32);
    //pio_sm_set_consecutive_pindirs(pio, sm, set_pin, 1, true);
    sm_config_set_in_pins(&c, in_pin);
    sm_config_set_set_pins(&c, set_pin, 1);
    sm_config_set_jmp_pin(&c, in_pin);
    pio_sm_init(pio, sm, offset, &c);
}

#endif

