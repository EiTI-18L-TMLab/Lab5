#include "../include/system.h"



void _clocks_init(void)
{
  /*
   * SMCLK - XT2 source, div by 4
   * MCLK  - DCO source, default 1MHz, no div
   *
   */

	BCSCTL1 &= ~XT2OFF;                       // XT2on
	volatile unsigned int i;

  do
  {
	  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
	  for (i = 0xFF; i > 0; i--);               // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  BCSCTL2 |= SELM_2 + SELS;                 // MCLK = SMCLK = XT2 (safe)
}

void _io_init(void)
{
    P1DIR = 0x00;
    P1IES = START_BUTTON | INTERTIME_BUTTON | RESET_BUTTON;
	P1IE =	START_BUTTON | INTERTIME_BUTTON | RESET_BUTTON;
	P2DIR |= 0xFF; //port 2 - wyjscie
}


void system_init(void)
{
  _clocks_init();
  timerA_init();
  P3SEL |= 0x30;                            // P3.4,5 = USART0 TXD/RXD
  // _io_init();
}


