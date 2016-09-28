/* Include Need */

/* UART & TIMER1 */


////////////////* UASRT Set Function *////////////////

/* At Asynchronous Normal mode (U2X = 0) */

/* USART Initial */
void USART_Init( unsigned long baud )
{
	/* Set baud rate */
	baud = F_CPU/16/baud-1;
	UBRRH = (unsigned char)(baud>>8);
	UBRRL = (unsigned char)baud;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXCIE)|(1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 1stop bit */
	UCSRC = (1<<UCSZ1)|(1<<UCSZ0);
}

/* USART Transmit */
void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) )
	;
	/* Put data into buffer, sends the data */
	UDR = data;
}

/* USART Transmit and turn char to ASCII */
void USART_Transmit_char_to_ASCII( unsigned char data )
{
	USART_Transmit( data/100   | 0x30 );
	USART_Transmit( data/10%10 | 0x30 );
	USART_Transmit( data%10    | 0x30 );
	USART_Transmit(',');
}

/* USART Receive */
unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) )
	;
	/* Get and return received data from buffer */
	return UDR;
}

/* USART Flush */
void USART_Flush( void )
{
	unsigned char dummy;
	while ( UCSRA & (1<<RXC) ) dummy = UDR;
}

/* USART Next (Change) line */
void Next_line( void )
{
	char str[]={10,13};
	int i;
	for(i=0;i<2;i++)
		USART_Transmit(str[i]);
}

////////////////* TIMER Set Function *////////////////

/* TIMER1 Initial */
void TIMER1_1sec_Init( void )
{
	/* Set Divide F_CPU By 1024 */
	TCCR1B = (1<<CS12)|(1<<CS10);
	/* Set TIMER1 Register Initial Value */
	TCNT1 = 65535-F_CPU/1024;
	/* TIMER1 Enable */
	TIMSK = (1<<TOIE1);
}

