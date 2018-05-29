#include "../include/uart.h"


uint8_t uart_init()
{
	int status = -1;

	/*
	 * http://daycounter.com/Calculators/MSP430-Uart-Calculator.phtml
	 * UART Clock = 7372.8
	 * Baud Rate = 115.2
	 * Number of bits = 11
	 * */

  
	  ME1 |= UTXE0 + URXE0;                     // Enable USART0 TXD/RXD
	  UCTL0 |= CHAR;                            // 8-bit character
	  UTCTL0 |= SSEL1;                          // UCLK = SMCLK
	  U0BR0 = 0x40;
	  U0BR1 = 0x00;
	  U0MCTL = 0x00;

	  UCTL0 &= ~SWRST;
	  	  	  // Initialize USART state machine
	  IE1 |= URXIE0;
	 //IE1 |= UTXIE0;

	return status;
}


uint8_t put_string(ring_buffer* buffer,char* putted)
{
	while (*putted != '\0')
	{
		if(buffer->numofelem == BUFF_SIZE)
			return 0;

		buffer->buf[buffer->head] = *putted;
		buffer->head = (buffer->head+1 < BUFF_SIZE) ? buffer->head+1 : 0;
		buffer->numofelem ++;
		putted++;
	}
	IE1 |= UTXIE0;  // wlaczenie przerwac - > zaczynmy wysylanie

	return 1;
}

uint8_t put_char(ring_buffer* buffer,char putted)
{

	if(buffer->numofelem == BUFF_SIZE)
		return 0;

	buffer->buf[buffer->head] = putted;
	buffer->head = (buffer->head+1 < BUFF_SIZE) ? buffer->head+1 : 0;
	buffer->numofelem ++;

	IE1 |= UTXIE0;  // wlaczenie przerwan - > zaczynmy wysylanie\

	return 1;
}

uint8_t pop(ring_buffer* buffer)
{
	if(buffer->numofelem == 0)
	{
		IE1 &= ~UTXIE0;
		//IFG1 |= UTXIFG0;
		return 0xFF;
	}

	buffer->numofelem--;

	// bufor pusty przestajemy wysylac
	if(buffer->numofelem == 0)
	{
			IE1 &= ~UTXIE0;
			//IFG1 |= UTXIFG0;
	}

	uint8_t temp = buffer->tail;
	buffer->tail = (buffer->tail+1 < BUFF_SIZE) ? buffer->tail+1 : 0;
	return buffer->buf[temp];
}

uint8_t put_char_rx(ring_buffer* buffer,char putted)
{

	if(buffer->numofelem == BUFF_SIZE)
		return 0;

	buffer->buf[buffer->head] = putted;
	buffer->head = (buffer->head+1 < BUFF_SIZE) ? buffer->head+1 : 0;
	buffer->numofelem ++;


	IE1 |= URXIE0;  // wlaczenie przerwan - > zaczynmy wysylanie\

	return 1;
}

uint8_t pop_rx(ring_buffer* buffer)
{
	if(buffer->numofelem == 0)
		return 0xFF;

	buffer->numofelem--;

	if(buffer->numofelem == 0)
	{
			IE1 &= ~UTXIE0;
	}

	uint8_t temp = buffer->tail;
	buffer->tail = (buffer->tail+1 < BUFF_SIZE) ? buffer->tail+1 : 0;
	return buffer->buf[temp];
}


