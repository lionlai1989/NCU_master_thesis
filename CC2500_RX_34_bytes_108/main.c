#include <avr\io.h>
#include <avr/interrupt.h>
#include <util\delay.h>
#include <UART&TIMER1.h>
#include <USI.h>
#include <CC1100.h>
#include <CC1100Control.h>
#include <RX&TX_Module.h>
#include <avr\pgmspace.h>

#define length 34
#define BufferNumber 2

char str1[] PROGMEM="RX:";

//unsigned char rxBuffer[32] = {51,50,49,48,51,50,49,48,51,50,49,48,51,50,49,48,51,50,49,48,51,50,49,48,51,50,49,48,51,50,49,48};
unsigned char rxBuffer[BufferNumber][length];
unsigned char Swapcount = 0;
volatile unsigned char flag = 1;	// RX Mode
	//						  0		   TX Mode
unsigned char i=0,j=0,outtx=1,garbage;
int y=0;
ISR( PCINT_vect )
{
	CC1100WriteStrobe( SRX );
	USART_Transmit( 0xAA );
	USART_Transmit( y );
	USART_Transmit( 0xAA );
	y++;
}
void pinchange_init(void)
{
	GIMSK |= (1<<PCIE);
	PCMSK |= (1<<PCINT3);
}
int main(void)
{
	int ii;
	USI_Init();
	USART_Init(230400);
	CC1100Initial();
//	USART_Transmit_char_to_ASCII( 0x6f );		// boot finished.(show 111)
	
	CC1100WriteStrobe( SIDLE );
	CC1100WriteStrobe( SFRX );
	CC1100WriteStrobe( SRX );
	
	for(ii=0;ii<5;ii++)
		_delay_ms(1000);
		
	sei();
// *** RX 32 bytes *** //

	while(1)
	{
		if(flag)
		{
			while( !CHKBIT(PINB, GDO0) )					// wait until RX start
				if(flag!=1)
					if( 0 == CC1100ReadStatus( RXBYTES ) )	// if at RX, copmlete RX before TX
						break;
			while(  CHKBIT(PINB, GDO0) )					// wati until RX finish
				if(flag!=1)
					if( 0 == CC1100ReadStatus( RXBYTES ) )	// if at RX, copmlete RX before TX
						break;
			if(flag)
			{
				//CC1100WriteStrobe( SRX );					// RX start again
				CC1100ReadFromRXFIFO( rxBuffer[Swapcount%2] , length );	// Read from the RX FIFO
				
//				for(i=0;i<3;i++)
//					USART_Transmit(pgm_read_byte(&str1[i]));
				
				for( i=0 ; i<length ; i++ )
					USART_Transmit( rxBuffer[Swapcount%2][i] );			// serial port output rxBuffer
			
				CC1100WriteStrobe( SIDLE );
				CC1100WriteStrobe( SFRX );
				CC1100WriteStrobe( SRX );
			}
		}
	}
}