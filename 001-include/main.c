#include "main.h"

int main() {
  stdio_init_all();
  sleep_ms(10000);

  while(true) {
    tight_loop_contents();
  }
   
}

