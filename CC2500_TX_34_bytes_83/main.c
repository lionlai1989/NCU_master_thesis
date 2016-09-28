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

char str2[] PROGMEM="TX:";

//unsigned char txBuffer[32] = {48,49,50,51,48,49,50,51,48,49,50,51,48,49,50,51,48,49,50,51,48,49,50,51,48,49,50,51,48,49,50,51};
unsigned char txBuffer[BufferNumber][length];
unsigned char RXSwapCount = 0;
unsigned char TXSwapCount = 0;
volatile unsigned char flag = 1;	// RX Mode
	//						  0		   TX Mode
unsigned char i=0,j=0,outtx=1,garbage;

ISR( SIG_USART0_RX )
{
	txBuffer[RXSwapCount%BufferNumber][j] = UDR;
	
	j++;
	if( j>(length-1) )
	{
		j=0;
		flag = 0;
		RXSwapCount++;
	}
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

// *** TX 32 bytes *** //

	while(1)
	{
		if(flag)
		{
			;
		}
			else
			{
				while(RXSwapCount != TXSwapCount)
				{
					CC1100WriteStrobe( SIDLE );
					CC1100WriteStrobe( SFTX );
					CC1100WriteStrobe( SFSTXON );
					CC1100WriteStrobe( STX );
				
					while(  CHKBIT(PINB, GDO0) ); 				// fill TX FIFO and start TX
					CC1100WriteToTXFIFO( txBuffer[TXSwapCount%BufferNumber] , length );	// Fill up the TX FIFO

//					for(i=0;i<3;i++)
//						USART_Transmit(pgm_read_byte(&str2[i]));

//					for( i=0 ; i<length ; i++ )
//						USART_Transmit( txBuffer[i] );			// serial port output txBuffer
					while( !CHKBIT(PINB, GDO0) );				// wait until RX start
					while(  CHKBIT(PINB, GDO0) );				// wati until RX finish
					TXSwapCount++;
				}
				flag = 1;
			}
		//flag = 0;		// 不做NONSTOP的時候要把這兩行註解掉
		//_delay_ms(500);
	}
}