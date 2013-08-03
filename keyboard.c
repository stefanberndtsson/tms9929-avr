#include "common.h"
#include "serial.h"
#include "keyboard.h"
#include "scancodes.h"

uint8_t is_shifted = 0;

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
  keyboard_poll();
  keyboard_poll();
  keyboard_poll();
  keyboard_poll();
  keyboard_poll();
  keyboard_poll();
  keyboard_poll();
}

uint8_t keyboard_poll() {
  uint8_t scancode = 0;
  scancode = serial_recv();
  if(scancode == 0x36 || scancode == 0x2a) {
    is_shifted = 1;
  }
  if(scancode == 0xb6 || scancode == 0xaa) {
    is_shifted = 0;
  }
  return scancode;
}

uint8_t keyboard_scan2ascii(uint8_t scancode) {
  uint16_t ascii;
  
  if(scancode&0x80) return 0;

  if(is_shifted) {
    ascii = scancodes_shift[scancode&0x7f];
  } else {
    ascii = scancodes_unshift[scancode&0x7f];
  }

  if(ascii > 0xff) return 0;
  return ascii&0xff;
}
