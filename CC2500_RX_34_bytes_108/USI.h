/***** USI Define for CC1100 By Attiny2313 *****/

#define USI_DI   PB5
#define USI_DO   PB6
#define USI_SCK  PB7
#define USI_SS   PD2

// void USI_Init( void );								USI initial
// void USI_Select( void );								USI chip select
// void USI_deselect( void );							USI chip deselect
// void USI_SCLK( void );								USI clock
// unsigned char USI_Transfer( unsigned char data );	USI transfer data and get state

void USI_Init( void )
{
	DDRB |= (1<<USI_DO)|(1<<USI_SCK);
	DDRD |= (1<<USI_SS);
	
	PORTB |= (1<<USI_DI)|(0<<USI_SCK);
	PORTD |= (1<<USI_SS);
	
	USICR |= (1<<USICS1)|(1<<USIWM0)|(0<<USICLK)|(0<<USITC);
}

void USI_Select( void )
{
	PORTD &= (0<<USI_SS);		// Chip Select
}

void USI_Deselect( void )
{
	PORTD |= (1<<USI_SS);		// Chip deSelect
}

void USI_SCLK( void )
{
	char i;
	
	USISR = (1<<USIOIF);
	for(i=0;i<8;i++)
	{
		USICR |= (1<<USITC);	// Write 1 to USITC,       SCK from 0 to 1
		USICR |= (1<<USITC);	// Write 1 to USITC again, SCK from 1 to 0
	}
}

unsigned char USI_Transfer( unsigned char data )
{	
	unsigned char state;
	
	USIDR = data;				// Write data to CC1100
	USI_SCLK();
	state = USIDR;
	
	return state;
}