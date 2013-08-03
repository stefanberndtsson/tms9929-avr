#include "common.h"
#include "serial.h"
#include "keyboard.h"

void keyboard_reset() {
  SBI(PORTD,KBD_RESET);
  delay_ms(2);
  CBI(PORTD,KBD_RESET);
  delay_ms(2);
  SBI(PORTD,KBD_RESET);
  delay_ms(2);
}

void keyboard_setup() {
  serial_send(0x80);
  serial_send(0x01);
  delay_ms(20);
  keyboard_reset();
}

uint8_t keyboard_poll() {
  return serial_recv();
}

