#define MEASURE_PIN 4
#define TEST_SQUAREWAVE_PIN 20

//Jumper GPIO 14 and 15
#define STATEMACHINE0_JMP_PIN 14
#define STATEMACHINE1_SET_PIN 15

#define STATEMACHINE0_IN_PIN MEASURE_PIN
#define STATEMACHINE1_IN_PIN MEASURE_PIN

int main() {
    PIO pio = pio0;
    uint32_t REFERENCE_FREQ = 125000000;
    
    uint offset1 = pio_add_program(pio, &countedges_program);
    uint offset2 = pio_add_program(pio, &referencetimer_program);

    uint sm0 = pio_claim_sm(pio, 0);
    uint sm1 = pio_claim_sm(pio, 1);
    
    countedges_program_init(pio, sm0, offset1, STATEMACHINE0_IN_PIN, STATEMACHINE0_JMP_PIN);
    referencetimer_program_init(pio, sm1, offset2, STATEMACHINE1_IN_PIN, STATEMACHINE1_SET_PIN);
    
    pio_sm_put_blocking(pio, sm1, REFERENCE_FREQ);
    pio_enable_sm_mask_in_sync(pio, 3);
    
    sleep_ms(2500);
    
    if (pio_sm_is_rx_fifo_empty(pio,sm0)) {
        return 0;
    }
    
    uint32_t countedges = pio_sm_get(pio, sm0);
    uint32_t extrapulsesreference = pio_sm_get(pio, sm1);
    uint32_t totalpulsesreference = REFERENCE_FREQ + 2*extrapulsesreference;
    double freq = (countedges + 1) * REFERENCE_FREQ/totalpulsesreference;
}
