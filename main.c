#include <avr/io.h>
#include "common.h"
#include "vdp.h"
#include "serial.h"
#include "keyboard.h"

#define AVR_DEBUG 3

void set_portd_bit(uint8_t bitnum) {
  PORTD |= _BV(bitnum);
}

void clr_portd_bit(uint8_t bitnum) {
  PORTD &= ~(_BV(bitnum));
}


void setup() {
  vdp_setup();
  serial_setup();
  keyboard_setup();
}

volatile uint8_t val = 0;
volatile uint16_t vraddr = 0;
volatile uint8_t kbdcode = 0;

volatile uint8_t hexnibble[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
				  '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void loop() {
  //  vdp_fill_vram((vraddr++)%(256)+64, val++, 1);
  //  PORTC=vraddr>>8;
  delay_ms(50);
  kbdcode = keyboard_poll();
  if(kbdcode) {
    vdp_print_str((uint8_t *)"Got: ");
    vdp_print(hexnibble[(kbdcode>>4)&0xf]);
    vdp_print(hexnibble[kbdcode&0xf]);
    vdp_print_newline();
    kbdcode = 0;
  }
}

int main(void) {
  setup();
  for(;;) loop();
  return 0;
}
