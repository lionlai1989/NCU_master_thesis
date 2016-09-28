/********** RF CC1100 RX & TX Module Function **********/

/********** RX Module Function **********/
unsigned char RX_Module( unsigned char *rxBuffer , unsigned char length )
{
	CC1100WriteStrobe( SIDLE );
	CC1100WriteStrobe( SFRX );
	CC1100WriteStrobe( SRX );
	
	while( !CHKBIT(PINB, GDO0) ); 				// wait until RX start
	while(  CHKBIT(PINB, GDO0) ); 				// wati until RX finish
	CC1100WriteStrobe( SRX );					// RX start again
	CC1100ReadFromRXFIFO( rxBuffer , length );	// Read from the RX FIFO
	
	return 1;
}

/********** TX Module Function **********/
unsigned char TX_Module( unsigned char *txBuffer , unsigned char length )
{
	CC1100WriteStrobe( SIDLE );
	CC1100WriteStrobe( SFTX );
	CC1100WriteStrobe( SFSTXON );
	CC1100WriteStrobe( STX );
	
	while( CHKBIT(PINB, GDO0) ); 				// fill TX FIFO and start TX
	CC1100WriteToTXFIFO( txBuffer , length );	// Fill up the TX FIFO
	CC1100WriteStrobe( STX );					// TX start again
	while( !CHKBIT(PINB, GDO0) );				// wait until TX start to continue

	return 1;
}