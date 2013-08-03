#include "common.h"
#include "vdp.h"
#include "atari8x8.h"

void mode_active() { SBI(PORTD,VDP_MODE); }
void mode_inactive() { CBI(PORTD,VDP_MODE); }
void csw_active() { CBI(PORTD,VDP_CSW); }
void csw_inactive() { SBI(PORTD,VDP_CSW);}
void csr_active() { CBI(PORTD,VDP_CSR); }
void csr_inactive() { SBI(PORTD,VDP_CSR); }
void reset_active() { CBI(PORTD,VDP_RESET); }
void reset_inactive() { SBI(PORTD,VDP_RESET); }
void out_data(uint8_t data) { PORTA = data; }

uint8_t in_data() { return PORTA; }

void vdp_reset() {
  reset_active();
  delay_ms(1);
  reset_inactive();
}

uint8_t vdp_read_status() {
  volatile uint8_t status;
  mode_active();
  csr_active();
  status = in_data();
  csr_inactive();
  return status;
}

void vdp_write_reg(uint8_t regnum, uint8_t data) {
  vdp_read_status();
  mode_active();
  csw_active();
  delay_us(1);
  out_data(data);
  csw_inactive();
  csw_active();
  delay_us(1);
  out_data(0x80|regnum);
  csw_inactive();
}

void vdp_write_vram(uint16_t addr, uint8_t data) {
  mode_active();
  csw_active();
  delay_us(1);
  out_data(addr);
  csw_inactive();
  csw_active();
  delay_us(1);
  out_data(0x40|((addr>>8)&0x3f));
  csw_inactive();
  mode_inactive();
  csw_active();
  delay_us(1);
  out_data(data);
  csw_inactive();
  mode_active();
}

void vdp_write_vram_buffer(uint16_t addr, uint8_t *data, uint16_t size, uint8_t pgm) {
  volatile uint16_t i;
  if(pgm) {
    for(i=0;i<size;i++) {
      vdp_write_vram(addr+i,pgm_read_byte(data+i));
    }
  } else {
    for(i=0;i<size;i++) {
      vdp_write_vram(addr+i,data[i]);
    }
  }
}

void vdp_fill_vram(uint16_t addr, uint8_t data, uint16_t size) {
  volatile uint16_t i;
  for(i=0;i<size;i++) {
    vdp_write_vram(addr+i,data);
  }
}


uint16_t vaddr = 0;
uint8_t cols[32] = {
  0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,
  0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,
  0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,
  0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1
};


uint8_t curs_col = 0;
uint8_t curs_row = 0;
uint8_t cursor = 0x07;

void vdp_print_cursor() {
  uint16_t pos;
  pos = curs_row * 32 + curs_col;
  vdp_write_vram(pos, cursor);
}

void vdp_clear_cursor() {
  uint16_t pos;
  pos = curs_row * 32 + curs_col;
  vdp_write_vram(pos, 0x00);
}

void vdp_print(uint8_t chr) {
  uint16_t pos;
  pos = curs_row * 32 + curs_col;
  vdp_write_vram(pos, chr);
  curs_col++;
  if(curs_col%32 == 0) {
    curs_col = 0;
    curs_row++;
    if(curs_row%24 == 0) {
      vdp_fill_vram(0x000, 0x00, 768);
      curs_row = 0;
    }
  }
  vdp_print_cursor();
}

void vdp_print_newline() {
  vdp_clear_cursor();
  curs_col = 0;
  curs_row++;
  if(curs_row%24 == 0) {
    vdp_fill_vram(0x000, 0x00, 768);
    curs_row = 0;
  }
  vdp_print_cursor();
}

void vdp_print_str(uint8_t *str) {
  while(*str) {
    vdp_print(*str++);
  }
}

void vdp_setup() {
  DDRA = 0xff;
  DDRC = 0xff;
  DDRD = 0xff;
  delay_s(2);
  mode_active();
  vdp_reset();
  PORTC=0x00;
  delay_ms(5);
  vdp_write_reg(0, 3);
  delay_ms(5);
  vdp_write_reg(1, VDP_CTRL_16K|VDP_CTRL_SHOW);
  vdp_write_reg(2, 0x00); // Name Table 0x400
  vdp_write_reg(3, 0x1f); // Color Table 0x200
  vdp_write_reg(4, 0x01); // Pattern Gen 0x800
  vdp_write_reg(5, 0x7f); // Sprite
  vdp_write_reg(6, 0x07); // Sprite
  vdp_write_reg(7, 0x1f); // Text Col
  vdp_read_status();

  vdp_fill_vram(0x0, 0x00, 16384); 
  vdp_fill_vram(0x40*0x1f, 0x1f, 32);
  vdp_write_vram_buffer(0x800, (uint8_t *)atari8x8, 2048, 1);
  //  vdp_write_vram_buffer(0x40*0x1f, (uint8_t *)cols, 32, 1);
  //  vdp_write_vram_buffer(0x0, "Hello World!", 12, 0);
  vdp_print_cursor();
}


