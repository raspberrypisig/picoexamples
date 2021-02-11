#include "main.h"
#define L 9

void tud_cdc_rx_wanted_cb(uint8_t itf, char wanted_char) { 
  reset_usb_boot(0, 0); 
} // go to flash mode

unsigned char strFromSerial[L+1];

unsigned char *readLine() {
  unsigned char u, *p;
  for(p=strFromSerial, u=getchar(); u!='\r' && p-strFromSerial<L; u=getchar())  putchar(*p++=u);
  *p = 0;  
  return strFromSerial;
}

int main() {
  stdio_init_all();
  sleep_ms(1000);
  tud_cdc_set_wanted_char('\0');

  int n;

  while(true) {
    printf("Ready to accept an integer from serial input. Enter number followed by enter key.\n");
    n=atoi(readLine());
    printf("\nThe number you entered: %d\n", n);
  }
   
}

