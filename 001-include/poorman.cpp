#include "poorman.h"

void tud_cdc_rx_wanted_cb(uint8_t itf, char wanted_char) { 
    reset_usb_boot(0, 0); 
} // go to flash mode
