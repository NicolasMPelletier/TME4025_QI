/*
 * 	UART3.c
 *  Created on	: Jan 15, 2017
 *  Author		: Nic Pelletier
 *  Description : Uses Pins PTC16 as RX
 *  			: Uses Pins PTC17 as TX
 *  			: Baud is 115200
 *  			: No flow control
 *  			: 1 stop and start bit
 *  			: No Parity
 *  Includes	: Uart3_Init to setup the Uart
 *  			: Uart3_Put to send an 8 bit value
 *  			: Uart3_Get to receive an 8 bit value
 *
 */
#include "fsl_device_registers.h"
#include "board.h"
#include "pin_mux.h"

#include "UART3.h"

void Uart3_Init()
{
	SIM_SCGC4 |= 0x2000; 								// Uart3 Gate
	SIM_SCGC5 |= 0x800;									// PortC Gate
	// MUX PINS
	PORTC_PCR16 |= PORT_PCR_MUX(3);						// RX Uart3
	PORTC_PCR17 |= PORT_PCR_MUX(3);						// TX Uart3
	// THIS IS ALL DONE TO CONFIGURE BAUD RATE
	UART3_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK); 	// TURN RX AND TX OFF
	UART3_C1=0;											// Set to Default
	uint16_t ubd = (uint16_t)((60*1000000)/(115200*16));// Calculate Baud
	uint8_t temp= UART3_BDH & ~(UART_BDH_SBR(0x1F)); 	// Save values except SBR
	UART3_BDH =temp| (((ubd &0x1F00)>>8));				// Set BAUD HIGH REG
	UART3_BDL = (uint8_t)(ubd& UART_BDL_SBR_MASK);		// Set Baud Low
	UART3_C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK);	// Enable TX RX
}

uint8_t Uart3_Get()
{
	while(!(UART3_S1 & UART_S1_RDRF_MASK));				// Block until a value is Ready
	return UART3_D;										// Return Value
}

void Uart3_Put(uint8_t SEND)
{
	while (!(UART3_S1 & UART_S1_TDRE_MASK)){};			// Block until there room to send
	UART3_D = SEND;										// Send
}
