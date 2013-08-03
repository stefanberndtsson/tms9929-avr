#include <avr/io.h>
#include "common.h"
#include "serial.h"

void serial_setup() {
  UCSRB |= (1 << RXEN) | (1 << TXEN);
  UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
  //  UBRRH = ((BAUD_PRESCALE >> 8))&0xff;
  //  UBRRL = (BAUD_PRESCALE&0xff);
  UBRRH = 0;
  UBRRL = 63;
}

void serial_send(uint8_t data) {
  while ((UCSRA & (1 << UDRE)) == 0) {};
  UDR = data;
}

uint8_t serial_recv() {
  while ((UCSRA & (1 << RXC)) == 0) {};
  return UDR;
}

