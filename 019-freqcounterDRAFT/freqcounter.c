int main() {
    // Choose which PIO instance to use (there are two instances)
    PIO pio = pio0;
    uint PIN_BASE = 10;

    // Our assembled program needs to be loaded into this PIO's instruction
    // memory. This SDK function will find a location (offset) in the
    // instruction memory where there is enough space for our program. We need
    // to remember this location!
    //uint offset = pio_add_program(pio, &hello_program);
    uint offset1 = pio_add_program(pio, &countedges_program);
    uint offset2 = pio_add_program(pio, &referencetimer_program);

    // Find a free state machine on our chosen PIO (erroring if there are
    // none). Configure it to run our program, and start it, using the
    // helper function we included in our .pio file.
    //uint sm = pio_claim_unused_sm(pio, true);
    //hello_program_init(pio, sm, offset, PICO_DEFAULT_LED_PIN);
    uint sm0 = pio_claim_sm(pio, 0);
    uint sm1 = pio_claim_sm(pio, 1);
    
    countedges_program_init(pio, sm0, offset1, PIN_BASE);
    referencetimer_program_init(pio, sm1, offset2, PIN_BASE);
    
    pio_enable_sm_mask_in_sync(pio, 3);
}
