/********** CC1100 Registers Address Define **********/

/********** Command Strobes **********/
#define SRES			0x30 // Reset chip.
#define SFSTXON			0x31 // Enable and calibrate frequency synthesizer (if MCSM0.FS_AUTOCAL=1). If in RX (with CCA): Go to a wait state where only the synthesizer is running (for quick RX / TX turnaround).
#define SXOFF			0x32 // Turn off crystal oscillator.
#define SCAL			0x33 // Calibrate frequency synthesizer and turn it off (enables quick start). SCAL can be strobed from IDLE mode without setting manual calibration mode (MCSM0.FS_AUTOCAL=0)
#define SRX				0x34 // Enable RX. Perform calibration first if coming from IDLE and MCSM0.FS_AUTOCAL=1.
#define STX				0x35 // In IDLE state: Enable TX. Perform calibration first if MCSM0.FS_AUTOCAL=1. If in RX state and CCA is enabled: Only go to TX if channel is clear.
#define SIDLE			0x36 // Exit RX / TX, turn off frequency synthesizer and exit Wake-On-Radio mode if applicable.
#define SAFC			0x37 // Perform AFC adjustment of the frequency synthesizer as outlined in section 22.1.
#define SWOR			0x38 // Start automatic RX polling sequence (Wake-on-Radio) as described in section 27.5.
#define SPWD			0x39 // Enter power down mode when CSn goes high.
#define SFRX			0x3A // Flush the RX FIFO buffer.
#define SFTX			0x3B // Flush the TX FIFO buffer.
#define SWORRST			0x3C // Reset real time clock.
#define SNOP			0x3D // No operation. May be used to pad strobe commands to two bytes for simpler software.

/********** Configuration Registers **********/
#define IOCFG2			0x00 // GDO2 output pin configuration
#define IOCFG1			0x01 // GDO1 output pin configuration
#define IOCFG0			0x02 // GDO0 output pin configuration
#define FIFOTHR			0x03 // RX FIFO and TX FIFO thresholds
#define SYNC1			0x04 // Sync word, high byte
#define SYNC0			0x05 // Sync word, low byte
#define PKTLEN			0x06 // Packet length
#define PKTCTRL1		0x07 // Packet automation control
#define PKTCTRL0		0x08 // Packet automation control
#define ADDR			0x09 // Device address
#define CHANNR			0x0A // Channel number
#define FSCTRL1			0x0B // Frequency synthesizer control
#define FSCTRL0			0x0C // Frequency synthesizer control
#define FREQ2			0x0D // Frequency control word, high byte
#define FREQ1			0x0E // Frequency control word, middle byte
#define FREQ0			0x0F // Frequency control word, low byte
#define MDMCFG4			0x10 // Modem configuration
#define MDMCFG3			0x11 // Modem configuration
#define MDMCFG2			0x12 // Modem configuration
#define MDMCFG1			0x13 // Modem configuration
#define MDMCFG0			0x14 // Modem configuration
#define DEVIATN			0x15 // Modem deviation setting
#define MCSM2			0x16 // Main Radio Control State Machine configuration
#define MCSM1			0x17 // Main Radio Control State Machine configuration
#define MCSM0			0x18 // Main Radio Control State Machine configuration
#define FOCCFG			0x19 // Frequency Offset Compensation configuration
#define BSCFG			0x1A // Bit Synchronization configuration
#define AGCTRL2			0x1B // AGC control
#define AGCTRL1			0x1C // AGC control
#define AGCTRL0			0x1D // AGC control
#define WOREVT1			0x1E // High byte Event 0 timeout
#define WOREVT0			0x1F // Low byte Event 0 timeout
#define WORCTRL			0x20 // Wake On Radio control
#define FREND1			0x21 // Front end RX configuration
#define FREND0			0x22 // Front end TX configuration
#define FSCAL3			0x23 // Frequency synthesizer calibration
#define FSCAL2			0x24 // Frequency synthesizer calibration
#define FSCAL1			0x25 // Frequency synthesizer calibration
#define FSCAL0			0x26 // Frequency synthesizer calibration
#define RCCTRL1			0x27 // RC oscillator configuration
#define RCCTRL0			0x28 // RC oscillator configuration
#define FSTEST			0x29 // Frequency synthesizer calibration control
#define PTEST			0x2A // Production test
#define AGCTEST			0x2B // AGC test
#define TEST2			0x2C // Various test settings
#define TEST1			0x2D // Various test settings
#define TEST0			0x2E // Various test settings

/********** Status Registers **********/
#define PARTNUM			0xF0 // Part number for CC1100 60
#define VERSION			0xF1 // Current version number 60
#define FREQEST			0xF2 // Frequency Offset Estimate 60
#define LQI				0xF3 // Demodulator estimate for Link Quality 60
#define RSSI			0xF4 // Received signal strength indication 61
#define MARCSTATE		0xF5 // Control state machine state 61
#define WORTIME1		0xF6 // High byte of WOR timer 61
#define WORTIME0		0xF7 // Low byte of WOR timer 62
#define PKTSTATUS		0xF8 // Current GDOx status and packet status 62
#define VCO_VC_DAC		0xF9 // Current setting from PLL calibration module 62
#define TXBYTES			0xFA // Underflow and number of bytes in the TX FIFO 62
#define RXBYTES			0xFB // Overflow and number of bytes in the RX FIFO

/********** (0xF5) MARCSTATE ¡V Main Radio Control State Machine state **********/
#define SLEEP			0x00 // SLEEP
#define IDLE			0x01 // IDLE
#define XOFF			0x02 // XOFF
#define VCOON_MC		0x03 // MANCAL
#define REGON_MC		0x04 // MANCAL
#define MANCAL			0x05 // MANCAL
#define VCOON			0x06 // FS_WAKEUP
#define REGON			0x07 // FS_WAKEUP
#define STARTCAL		0x08 // CALIBRATE
#define BWBOOST			0x09 // SETTLING
#define FS_LOCK			0x0A // SETTLING
#define IFADCON			0x0B // SETTLING
#define ENDCAL			0x0C // CALIBRATE
#define RX				0x0D // RX
#define RX_END			0x0E // RX
#define RX_RST			0x0F // RX
#define TXRX_SWITCH		0x10 // TXRX_SETTLING
#define RX_OVERFLOW		0x11 // RX_OVERFLOW
#define FSTXON			0x12 // FSTXON
#define TX				0x13 // TX
#define TX_END			0x14 // TX
#define RXTX_SWITCH		0x15 // RXTX_SETTLING
#define TX_UNDERFLOW	0x16 // TX_UNDERFLOW

/********** Output Power **********/
#define PATABLE			0x3E

/********** FIFO Registers **********/
#define TX_FIFO			0x7F
#define RX_FIFO			0xFF