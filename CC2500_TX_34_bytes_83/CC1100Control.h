/********** CC1100 Control Function **********/

#define GDO_PORT	PINB
#define GDO0		PB3
#define GDO1		PB5	// the same as SPI_MISO
#define GDO2		PB4
#define CHKBIT(ADDRESS,BIT) ( ADDRESS & (1<<BIT) )

void CC1100WriteStrobe( unsigned char addr )
{
	USI_Select();
	USI_Transfer( addr );
	USI_Deselect();
}

void CC1100WriteRegister( unsigned char addr , unsigned char data )
{
	USI_Select();
	USI_Transfer( addr );
	USI_Transfer( data );
	USI_Deselect();
}

unsigned char CC1100ReadStatus( unsigned char addr )
{
	unsigned char state;

	USI_Select();
	USI_Transfer( addr );
	state = USI_Transfer( 0x00 );
	USI_Deselect();
	
	return state;
}

void CC1100WriteToTXFIFO( unsigned char *data , unsigned char bytes )
{
	unsigned char i;

	USI_Select();
	USI_Transfer( TX_FIFO );
	for( i=0 ; i<bytes ; i++ )
		USI_Transfer( data[i] );
	USI_Deselect();
}

void CC1100ReadFromRXFIFO( unsigned char *data , unsigned char bytes )
{
	unsigned char i;

	USI_Select();
	USI_Transfer( RX_FIFO );
	for( i=0 ; i<bytes ; i++ )
		data[i] = USI_Transfer( 0x00 );
	USI_Deselect();
}

void CC1100Initial( void )
{
//	unsigned char paTable = 0x06;	// PATABLE (-10 dBm output power433)
//	unsigned char paTable = 0x3A;	// PATABLE ( -5 dBm output power433)
	unsigned char paTable = 0xFE;	// PATABLE (  0 dBm output power433)
//	unsigned char paTable = 0x85;	// PATABLE (  5 dBm output power433)
//	unsigned char paTable = 0xC0;	// PATABLE ( 10 dBm output power433)
//	unsigned char paTable = 0xFF;	// PATABLE (  1 dBm output power2.4)
//	unsigned char paTable = 0x50;	// PATABLE (-30 dBm output power2.4)
//	unsigned char paTable = 0x00;	// PATABLE (-55 dBm output power2.4)
/*	
//	#include "setting_433MHz_2k4bps.txt"
// 以下全改成給2.4GHz用
	CC1100WriteRegister( FIFOTHR , 0x07 );		// FIFO_THR = 7, 33 bytes in TX FIFO
	CC1100WriteRegister( PATABLE , paTable );		// PATABLE
	
	CC1100WriteRegister( PKTCTRL0 , 0x00 );
	CC1100WriteRegister( PKTLEN , 0x22 );
	CC1100WriteRegister( IOCFG0 , 0x06 );
	CC1100WriteRegister( IOCFG2 , 0x02 );
	
	CC1100WriteRegister( FSCTRL1 , 0x08 );		// Frequency synthesizer control.
	CC1100WriteRegister( FSCTRL0 , 0x00 );		// Frequency synthesizer control.
	CC1100WriteRegister( FREQ2 , 0x5D );		// Frequency control word, high byte.
	CC1100WriteRegister( FREQ1 , 0x93 );		// Frequency control word, middle byte.
	CC1100WriteRegister( FREQ0 , 0xB1 );		// Frequency control word, low byte.
	
	CC1100WriteRegister( MDMCFG4 , 0x86 );		// Modem configuration.
	CC1100WriteRegister( MDMCFG3 , 0x83 );		// Modem configuration.
	CC1100WriteRegister( MDMCFG2 , 0x03 );		// Modem configuration.
	CC1100WriteRegister( MDMCFG1 , 0x22 );		// Modem configuration.
	CC1100WriteRegister( MDMCFG0 , 0xF8 );		// Modem configuration.
//	CC1100WriteRegister( CHANNR , 0x00 );		// Channel number.
	CC1100WriteRegister( CHANNR , 0xF5 );		// Channel number.
	CC1100WriteRegister( DEVIATN , 0x44 );		// Modem deviation setting (when FSK modulation is enabled).
	CC1100WriteRegister( FREND1 , 0x56 );		// Front end RX configuration.
	CC1100WriteRegister( FREND0 , 0x10 );		// Front end RX configuration.
	CC1100WriteRegister( MCSM1 , 0x33 );		// Main Radio Control State Machine configuration.
	CC1100WriteRegister( MCSM0 , 0x18 );		// Main Radio Control State Machine configuration.
	CC1100WriteRegister( FOCCFG , 0x16 );		// Frequency Offset Compensation Configuration.
	CC1100WriteRegister( FSCAL3 , 0xA9 );		// Frequency synthesizer calibration.
	CC1100WriteRegister( FSCAL2 , 0x0A );		// Frequency synthesizer calibration.
	CC1100WriteRegister( FSCAL1 , 0x00 );		// Frequency synthesizer calibration.
	CC1100WriteRegister( FSCAL0 , 0x11 );		// Frequency synthesizer calibration.
	CC1100WriteRegister( PKTCTRL1 , 0x00 );		// no append_status
*/

// 76k8Baud
// 以下全改成給2.4GHz用
	CC1100WriteRegister( FIFOTHR , 0x07 );		// FIFO_THR = 7, 33 bytes in TX FIFO
	CC1100WriteRegister( PATABLE , paTable );		// PATABLE
	CC1100WriteRegister( PKTCTRL1 , 0x08 );		// no append_status
	CC1100WriteRegister( PKTCTRL0 , 0x04 );
	CC1100WriteRegister( PKTLEN , 0x22 );
	CC1100WriteRegister( IOCFG0 , 0x06 );
	CC1100WriteRegister( IOCFG2 , 0x02 );
	
	CC1100WriteRegister( FSCTRL1 , 0x0B );		// Frequency synthesizer control.
	CC1100WriteRegister( FSCTRL0 , 0x00 );		// Frequency synthesizer control.
	CC1100WriteRegister( FREQ2 , 0x5D );		// Frequency control word, high byte.
	CC1100WriteRegister( FREQ1 , 0x93 );		// Frequency control word, middle byte.
	CC1100WriteRegister( FREQ0 , 0xB1 );		// Frequency control word, low byte.
	
	CC1100WriteRegister( MDMCFG4 , 0x7B );		// Modem configuration.
	CC1100WriteRegister( MDMCFG3 , 0x83 );		// Modem configuration.
	CC1100WriteRegister( MDMCFG2 , 0x83 );		// Modem configuration.
	CC1100WriteRegister( MDMCFG1 , 0x22 );		// Modem configuration.
	CC1100WriteRegister( MDMCFG0 , 0xF8 );		// Modem configuration.
//	CC1100WriteRegister( CHANNR , 0x00 );		// Channel number.
	CC1100WriteRegister( CHANNR , 83 );		// Channel number.
	CC1100WriteRegister( DEVIATN , 0x44 );		// Modem deviation setting (when FSK modulation is enabled).
	CC1100WriteRegister( FREND1 , 0x56 );		// Front end RX configuration.
	CC1100WriteRegister( FREND0 , 0x10 );		// Front end RX configuration.
	CC1100WriteRegister( MCSM1 , 0x33 );		// Main Radio Control State Machine configuration.
	CC1100WriteRegister( MCSM0 , 0x18 );		// Main Radio Control State Machine configuration.
	CC1100WriteRegister( FOCCFG , 0x16 );		// Frequency Offset Compensation Configuration.
//	CC1100WriteRegister( BSCFG , 0x6C );
	CC1100WriteRegister( AGCTRL2 , 0x43 );
	CC1100WriteRegister( AGCTRL1 , 0x40 );
	CC1100WriteRegister( AGCTRL0 , 0x91 );
	CC1100WriteRegister( FSCAL3 , 0xA9 );		// Frequency synthesizer calibration.
	CC1100WriteRegister( FSCAL2 , 0x0A );		// Frequency synthesizer calibration.
	CC1100WriteRegister( FSCAL1 , 0x00 );		// Frequency synthesizer calibration.
	CC1100WriteRegister( FSCAL0 , 0x11 );		// Frequency synthesizer calibration.
	CC1100WriteRegister( FSTEST , 0x59 );
	CC1100WriteRegister( TEST2 , 0x88 );
	CC1100WriteRegister( TEST1 , 0x31 );
	CC1100WriteRegister( TEST0 , 0x0B );
/*
// 250kBaud
// 以下全改成給2.4GHz用
	CC1100WriteRegister( FIFOTHR , 0x07 );		// FIFO_THR = 7, 33 bytes in TX FIFO
	CC1100WriteRegister( PATABLE , paTable );		// PATABLE
	CC1100WriteRegister( PKTCTRL1 , 0x08 );		// no append_status
	CC1100WriteRegister( PKTCTRL0 , 0x04 );
	CC1100WriteRegister( PKTLEN , 0x22 );
	CC1100WriteRegister( IOCFG0 , 0x06 );
	CC1100WriteRegister( IOCFG2 , 0x02 );
	
	CC1100WriteRegister( FSCTRL1 , 0x12 );		// Frequency synthesizer control.
	CC1100WriteRegister( FSCTRL0 , 0x00 );		// Frequency synthesizer control.
	CC1100WriteRegister( FREQ2 , 0x5C );		// Frequency control word, high byte.
	CC1100WriteRegister( FREQ1 , 0x53 );		// Frequency control word, middle byte.
	CC1100WriteRegister( FREQ0 , 0xB1 );		// Frequency control word, low byte.
	
	CC1100WriteRegister( MDMCFG4 , 0x2D );		// Modem configuration.
	CC1100WriteRegister( MDMCFG3 , 0x3B );		// Modem configuration.
	CC1100WriteRegister( MDMCFG2 , 0xF3 );		// Modem configuration.
	CC1100WriteRegister( MDMCFG1 , 0xB2 );		// Modem configuration.
	CC1100WriteRegister( MDMCFG0 , 0xF8 );		// Modem configuration.
//	CC1100WriteRegister( CHANNR , 0x00 );		// Channel number.
	CC1100WriteRegister( CHANNR , 0xF5 );		// Channel number.
	CC1100WriteRegister( DEVIATN , 0x00 );		// Modem deviation setting (when FSK modulation is enabled).
	CC1100WriteRegister( FREND1 , 0xB6 );		// Front end RX configuration.
	CC1100WriteRegister( FREND0 , 0x10 );		// Front end RX configuration.
	CC1100WriteRegister( MCSM1 , 0x34 );		// Main Radio Control State Machine configuration.
	CC1100WriteRegister( MCSM0 , 0x18 );		// Main Radio Control State Machine configuration.
	CC1100WriteRegister( FOCCFG , 0x1D );		// Frequency Offset Compensation Configuration.
	CC1100WriteRegister( BSCFG , 0x1C );
	CC1100WriteRegister( AGCTRL2 , 0xC7 );
	CC1100WriteRegister( AGCTRL1 , 0x00 );
	CC1100WriteRegister( AGCTRL0 , 0xB2 );
	CC1100WriteRegister( FSCAL3 , 0xEA );		// Frequency synthesizer calibration.
	CC1100WriteRegister( FSCAL2 , 0x0A );		// Frequency synthesizer calibration.
	CC1100WriteRegister( FSCAL1 , 0x00 );		// Frequency synthesizer calibration.
	CC1100WriteRegister( FSCAL0 , 0x11 );		// Frequency synthesizer calibration.
	CC1100WriteRegister( FSTEST , 0x59 );
*/
}