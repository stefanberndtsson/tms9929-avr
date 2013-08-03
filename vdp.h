#ifndef VDP_H
#define VDP_H

#define VDP_NONE         0x00
#define VDP_CTRL_M3      0x02
#define VDP_CTRL_EXTVID  0x01

#define VDP_CTRL_16K     0x80
#define VDP_CTRL_SHOW    0x40
#define VDP_CTRL_IRQ     0x20
#define VDP_CTRL_M1      0x10
#define VDP_CTRL_M2      0x08
#define VDP_CTRL_SPRLRGE 0x02
#define VDP_CTRL_SPRZOOM 0x01

#define VDP_MODE  4
#define VDP_CSW   5
#define VDP_CSR   6
#define VDP_RESET 7

void vdp_setup();
void vdp_print(uint8_t chr);
void vdp_print_str(uint8_t *str);
void vdp_print_newline();
void vdp_delete_left();

#endif /* VDP_H */
