#include "main.h"
#define L 5

unsigned char strFromSerial[L+1];

unsigned char *readLine() {
  unsigned char u, *p;
  for(p=strFromSerial, u=getchar(); u!='\n' && p-strFromSerial<L; u=getchar())  putchar(*p++=u);
  *p = 0;  
  return strFromSerial;
}



int main() {
  stdio_init_all();
  sleep_ms(10000);

  int n;

  while(true) {
    printf("Ready to accept an integer from serial input. Enter number followed by enter key.\n");
    n=atoi(readLine());
    printf("\nThe number you entered: %d\n", n);
  }
   
}

