#include <msp430.h> 
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "format.h"
#include "data_buffer.h"

#define RX_BUFFER_INDEX 100 /* <=255 */
DATA_BUFFER_CREATE(rx_data_buffer_tab, RX_BUFFER_INDEX, rxBuf)

#define TX_BUFFER_INDEX 110 /* <=255 */
DATA_BUFFER_CREATE(tx_data_buffer_tab, TX_BUFFER_INDEX, txBuf)

char app_buffer[105];

volatile bool applicationIsReady=false;

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	// led debug
    P1DIR |= BIT4;
    P1SEL |= BIT4;

    // TX and RX pin conf
    P3DIR |= BIT4;
    P3SEL |= BIT5 | BIT4;
    // clock config
	BCSCTL1 = RSEL2 | RSEL0;
	DCOCTL = DCO0;
	// uart conf
    U0CTL = CHAR;
    U0TCTL = SSEL1 | SSEL0;
    U0RCTL = URXEIE;
    U0BR1 = 0;
    U0BR0 = 0x09;
    U0MCTL = 0x08;
    ME1 = UTXE0 | URXE0;
    IE1 = /*UTXIE0 |*/ URXIE0;
    IFG1 &= ~UTXIFG0;
/*
    // Hello text
    char helloString[] = "Hello im my MSP430 world, please type text to format: \r";
    int i;
	for(i=0; i<strlen(helloString); i++)
		data_buffer_write(&txBuf, helloString[i]);
	TXBUF0 = data_buffer_read(&txBuf);
	IE1 |= UTXIE0; // enable TX
*/
    applicationIsReady = true;
    while (1) {
    	__bis_SR_register(GIE + CPUOFF);
    	applicationIsReady = false;
    	textFormat(app_buffer);

    	int i;
    	for (i=0;i <= (mystrlen(app_buffer)-1);i++)
    		data_buffer_write(&txBuf, app_buffer[i]);
    	data_buffer_write(&txBuf, '\n');

    	TXBUF0 = data_buffer_read(&txBuf);
    	IE1 |= UTXIE0; // enable TX
    	applicationIsReady = true;
    }

}

#pragma vector=USART0RX_VECTOR
__interrupt void USART0_RX (void) {
	char received;
	received = RXBUF0;

	if(DATA_BUFFER_READY_TO_WRITE(rxBuf))
		data_buffer_write(&rxBuf, received);

	if( DATA_BUFFER_FULL_FLAG_IS_SET(rxBuf) )
	{
		TXBUF0 = '\a';
		received = '\r';
	}

	//sprawdzanie czy wyslac to do aplikacji
	if(received == '\r' && (applicationIsReady==true))
	{
		applicationIsReady = false;
		//otworz aplikacje
		uint16_t n = 0;
		while(data_buffer_number(&rxBuf) > 0){
			app_buffer[n] = data_buffer_read(&rxBuf);
			n++;
			if(app_buffer[n-1]=='\r')
				break;
		}
		app_buffer[n] = 0;
		__bic_SR_register_on_exit(CPUOFF);
	}
}

#pragma vector=USART0TX_VECTOR
__interrupt void USART0_TX (void)
{
		if(data_buffer_number(&txBuf)>0) TXBUF0 = data_buffer_read(&txBuf);
		else
			IE1 &= ~UTXIE0; // wylacz przerwania od TX
}

