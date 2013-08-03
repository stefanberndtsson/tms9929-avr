#include <avr/io.h>
#include "atari8x8.h"

#define VDP_MODE  4
#define VDP_CSW   5
#define VDP_CSR   6
#define VDP_RESET 7

#define AVR_DEBUG 3

void delay_ms(uint8_t ms) {
    uint16_t delay_count = F_CPU / 17500;
    volatile uint16_t i;
    
    while (ms != 0) {
        for (i=0; i != delay_count; i++);
        ms--;
    }
}

void delay_us(uint8_t us) {
    while (us != 0) {
        us--;
	us++;
	us--;
	us++;
        us--;
	us++;
	us--;
    }
}

void delay_s(uint8_t s) {
  while(s != 0) {
    delay_ms(250);
    delay_ms(250);
    delay_ms(250);
    delay_ms(250);
    s--;
  }
}

void set_portd_bit(uint8_t bitnum) {
  PORTD |= _BV(bitnum);
}

void clr_portd_bit(uint8_t bitnum) {
  PORTD &= ~(_BV(bitnum));
}

void mode_active() { set_portd_bit(VDP_MODE); }
void mode_inactive() { clr_portd_bit(VDP_MODE); }
void csw_active() { clr_portd_bit(VDP_CSW); }
void csw_inactive() { set_portd_bit(VDP_CSW);}
void csr_active() { clr_portd_bit(VDP_CSR); }
void csr_inactive() { set_portd_bit(VDP_CSR); }
void reset_active() { clr_portd_bit(VDP_RESET); }
void reset_inactive() { set_portd_bit(VDP_RESET); }
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

uint16_t vaddr = 0;
uint8_t cols[32] = {
  0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,
  0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,
  0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,
  0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1
};

void setup() {
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
  vdp_write_vram_buffer(0x0, "Hello World!", 12, 0);
}

volatile uint8_t val = 0;
volatile uint16_t vraddr = 0;

void loop() {
  vdp_fill_vram((vraddr++)%(256)+64, val++, 1);
  PORTC=vraddr>>8;
  delay_ms(50);
}

int main(void) {
  setup();
  for(;;) loop();
  return 0;
}
