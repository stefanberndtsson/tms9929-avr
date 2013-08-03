#ifndef SERIAL_H
#define SERIAL_H

#define USART_BAUDRATE 7812
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16))) - 1)

void serial_setup();
void serial_send(uint8_t data);
uint8_t serial_recv();

#endif /* SERIAL_H */
