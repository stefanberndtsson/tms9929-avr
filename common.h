#ifndef COMMON_H
#define COMMON_H

#include <avr/io.h>

#define SBI(port,bit) port |= _BV(bit);
#define CBI(port,bit) port &= ~(_BV(bit));

void delay_s(uint8_t delay);
void delay_ms(uint8_t delay);
void delay_us(uint8_t delay);

#endif /* COMMON_H */
