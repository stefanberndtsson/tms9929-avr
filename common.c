#include "common.h"

void delay_ms(uint8_t ms) {
    uint16_t delay_count = F_CPU / 17500;
    volatile uint16_t i;
    
    while (ms != 0) {
        for (i=0; i != delay_count; i++);
        ms--;
    }
}

void delay_us(uint8_t us) {
    while (us != 0) {
        us--;
	us++;
	us--;
	us++;
        us--;
	us++;
	us--;
    }
}

void delay_s(uint8_t s) {
  while(s != 0) {
    delay_ms(250);
    delay_ms(250);
    delay_ms(250);
    delay_ms(250);
    s--;
  }
}

