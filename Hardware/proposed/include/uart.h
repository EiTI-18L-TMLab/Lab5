#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H_


#include <stdint.h>
#include <msp430.h>
#define BUFF_SIZE 128



typedef volatile struct {
	 uint8_t buf[BUFF_SIZE];
     uint8_t head;
     uint8_t tail;
     uint8_t numofelem;
} ring_buffer;

ring_buffer buffor_tx;
ring_buffer buffor_rx;


uint8_t uart_init();
uint8_t put_string(ring_buffer* buffer,char* putted);
uint8_t put_char(ring_buffer* buffer,char putted);
uint8_t pop(ring_buffer*);

uint8_t put_char_rx(ring_buffer* buffer,char putted);
uint8_t pop_rx(ring_buffer*);


#endif /* INCLUDE_UART_H_ */
