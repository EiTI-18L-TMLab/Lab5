#include <msp430.h> 

/*
 * PORT1 - DIODY
 *
 *
 * PORT3 - UART
 * 		P3.3 - Receive data in
 * 		P3.4 - Transmit data out
 *
 */

/*
 * main.c
 */

// bity uart
#define TXD BIT4
#define RXD BIT3

// bity ledow do sprawdzania poprawnosci transmisji
#define TXLED BIT1
#define RXLED BIT0

void reset_all_ports()
{
	P1DIR = 0xFF; //all output
	P1OUT = 0xFF; //all set

	P2DIR = 0xFF; //all output
	P2OUT = 0x00; //all reset

	P3DIR = 0xFF; //all output
	P3OUT = 0x00; //all reset

	P4DIR = 0xFF; //all output
	P4OUT = 0x00; //all reset

	P5DIR = 0xFF; //all output
	P5OUT = 0x00; //all reset

	P6DIR = 0xFF; //all output
	P6OUT &= 0x00; //all reset
}

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	DCOCTL = 0x00;

	UCA0CTL1 |= UCSSEL_2; // SMCLK
	//dwubajtowy rejest  baud rate control
	UCA0BR0 = 0x08; // 1MHz 115200
	UCA0BR1 = 0x00; // 1MHz 115200

	UCA0MCTL = UCBRS2 +  UCBRS1 + UCBRS0; // Modulation UCBRSx = 6  Z TABELKI
	UCA0CTL1 &= ~UCSWRST; // Software reset enable 0 Disabled. USCI reset released for operation.
	UC0IE |= UCA0RXIE; // Enable USCI_A0 RX interrupt
	
	reset_all_ports();
    P3SEL |= TXD + RXD; //turn on uart

    __bis_SR_register(CPUOFF + GIE); //enter  LPM0

	return 0;
}


//transmit
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
{
   P1OUT |= TXLED;

	//interrupt body here

   P1OUT &= ~TXLED;
}

//receive
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	P1OUT |= RXLED;

	//interrupt body here

	P1OUT &= ~RXLED;
}
