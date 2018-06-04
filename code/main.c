#include <msp430.h> 
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "format.h"
#include "data_buffer.h"

//CircularBuffer *rxBuf;
//CircularBuffer *txBuf;

#define RX_BUFFER_INDEX 100 /* <=255 */
DATA_BUFFER_CREATE(rx_data_buffer_tab, RX_BUFFER_INDEX, rxBuf)

#define TX_BUFFER_INDEX 100 /* <=255 */
DATA_BUFFER_CREATE(tx_data_buffer_tab, TX_BUFFER_INDEX, txBuf)

char app_buffer[100];

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    P1DIR |= BIT4;
    P1SEL |= BIT4;

    P3DIR |= BIT4;
    P3SEL |= BIT5 | BIT4;


	BCSCTL1 = RSEL2 | RSEL0;
	DCOCTL = DCO0;

    U0CTL = CHAR;
    U0TCTL = SSEL1 | SSEL0;
    U0RCTL = URXEIE;
    U0BR1 = 0;
    U0BR0 = 0x09;
    U0MCTL = 0x08;
    ME1 = UTXE0 | URXE0;
    IE1 = /*UTXIE0 |*/ URXIE0;
    IFG1 &= ~UTXIFG0;

    //char* app_buffer = malloc(100*sizeof(char));
    //char app_buffer[100];

    __bis_SR_register(GIE + CPUOFF);


    while (1) {
    	textFormat(app_buffer);
    	int i = 0;
    	//TXBUF0 = app_buffer[0];
		data_buffer_write(&txBuf, '\n');
    	while (i <= mystrlen(app_buffer))
    	{
    		//if(i==2) IFG1 |= UTXIFG0;
    		data_buffer_write(&txBuf, app_buffer[i]);
    		i++;
    	}
    	IE1 |= UTXIE0;
    	__bis_SR_register(GIE + CPUOFF);
    }

}

#pragma vector=USART0RX_VECTOR
__interrupt void USART0_RX (void) {
	char received;
	received = RXBUF0;

	if(DATA_BUFFER_READY_TO_WRITE(rxBuf))
		data_buffer_write(&rxBuf, received);
	TXBUF0 = received; //echo

	//sprawdzanie czy wyslac to do aplikacji

	if(received == '\r'){

		//otworz aplikacje
		data_buffer_write(&rxBuf, '\n');
		//app_buffer[0] = '\n';
		uint8_t n = 0;
		while(data_buffer_number(&rxBuf) > 0){
			app_buffer[n] = data_buffer_read(&rxBuf);
			n++;
		}
		//DATA_BUFFER_CLEAR(rxBuf)
		//app_buffer[n] = '\n';
		__bic_SR_register_on_exit(CPUOFF);

	}

}

#pragma vector=USART0TX_VECTOR
__interrupt void USART0_TX (void) {
		//while( data_buffer_number(&txBuf)>0 ) TXBUF0 = data_buffer_read(&txBuf);
		if(data_buffer_number(&txBuf)>0) TXBUF0 = data_buffer_read(&txBuf);
		else
			IE1 &= ~UTXIE0; // wylacz przerwania od TX

}

