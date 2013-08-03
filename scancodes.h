#ifndef SCANCODES_H
#define SCANCODES_H

#define KBD_NONE 0xffff
#define KBD_LEFT_CTRL 0xff01
#define KBD_LEFT_SHIFT 0xff02
#define KBD_RIGHT_SHIFT 0xff03
#define KBD_LEFT_ALT 0xff04
#define KBD_CAPS_LOCK 0xff05
#define KBD_F1 0xff06
#define KBD_F2 0xff07
#define KBD_F3 0xff08
#define KBD_F4 0xff09
#define KBD_F5 0xff0a
#define KBD_F6 0xff0b
#define KBD_F7 0xff0c
#define KBD_F8 0xff0d
#define KBD_F9 0xff0e
#define KBD_F10 0xff0f
#define KBD_CLRHOME 0xff10
#define KBD_UP_ARROW 0xff11
#define KBD_LEFT_ARROW 0xff12
#define KBD_RIGHT_ARROW 0xff13
#define KBD_DOWN_ARROW 0xff14
#define KBD_INSERT 0xff15
#define KBD_DELETE 0xff16
#define KBD_ISO 0xff17
#define KBD_UNDO 0xff18
#define KBD_HELP 0xff19

uint16_t scancodes_unshift[128] = {
  KBD_NONE,
  0x1b, '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '=', KBD_NONE, 0x09,
  0x08, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0x13,
  KBD_LEFT_CTRL, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 0x27, '\\',
  KBD_LEFT_SHIFT, 0x7e, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', KBD_RIGHT_SHIFT, KBD_NONE,
  KBD_LEFT_ALT, ' ', KBD_CAPS_LOCK,
  KBD_F1, KBD_F2, KBD_F3, KBD_F4, KBD_F5, KBD_F6, KBD_F7, KBD_F8, KBD_F9, KBD_F10,
  KBD_NONE, KBD_NONE, KBD_CLRHOME, KBD_UP_ARROW, KBD_NONE, '-',
  KBD_LEFT_ARROW, KBD_NONE, KBD_RIGHT_ARROW, '+', KBD_NONE, KBD_DOWN_ARROW, KBD_NONE, 
  KBD_INSERT, KBD_DELETE,
  KBD_NONE, KBD_NONE, KBD_NONE, KBD_NONE, KBD_NONE, KBD_NONE,
  KBD_NONE, KBD_NONE, KBD_NONE, KBD_NONE, KBD_NONE, KBD_NONE, 
  KBD_ISO, KBD_UNDO, KBD_HELP,
  '(', ')', '/', '*', '7', '8', '9', '4', '5', '6', '1', '2', '3', '0', '.', 0x13
};

uint16_t scancodes_shift[128] = {
  KBD_NONE,
  0x1b, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', KBD_NONE, 0x09,
  0x08, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 0x13,
  KBD_LEFT_CTRL, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '|',
  KBD_LEFT_SHIFT, 0x7e, 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', KBD_RIGHT_SHIFT, KBD_NONE,
  KBD_LEFT_ALT, ' ', KBD_CAPS_LOCK,
  KBD_F1, KBD_F2, KBD_F3, KBD_F4, KBD_F5, KBD_F6, KBD_F7, KBD_F8, KBD_F9, KBD_F10,
  KBD_NONE, KBD_NONE, KBD_CLRHOME, KBD_UP_ARROW, KBD_NONE, '-',
  KBD_LEFT_ARROW, KBD_NONE, KBD_RIGHT_ARROW, '+', KBD_NONE, KBD_DOWN_ARROW, KBD_NONE, 
  KBD_INSERT, KBD_DELETE,
  KBD_NONE, KBD_NONE, KBD_NONE, KBD_NONE, KBD_NONE, KBD_NONE,
  KBD_NONE, KBD_NONE, KBD_NONE, KBD_NONE, KBD_NONE, KBD_NONE, 
  KBD_ISO, KBD_UNDO, KBD_HELP,
  '(', ')', '/', '*', '7', '8', '9', '4', '5', '6', '1', '2', '3', '0', '.', 0x13
};

#endif /* SCANCODES_H */
