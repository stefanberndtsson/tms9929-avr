#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KBD_RESET 2
#define KBD_DOWN(x) (!(x&0x80));
#define KBD_UP(x) (!!(x&0x80));

void keyboard_setup();
uint8_t keyboard_poll();
void keyboard_cmd(uint8_t cmd);
uint8_t keyboard_scan2ascii(uint8_t scan);

#endif /* KEYBOARD_H */
