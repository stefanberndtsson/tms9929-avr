#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KBD_RESET 2

void keyboard_setup();
uint8_t keyboard_poll();
void keyboard_cmd(uint8_t cmd);

#endif /* KEYBOARD_H */
