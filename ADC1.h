/*
 * ADC1.h
 *
 *  Created on	: Jan 15, 2017
 *  Author		: Nic
 *  Description : Uses Pins PTC16 as RX
 *  			: Uses Pins PTC17 as TX
 *  			: Baud is 115200
 *  			: No flow control
 *  			: 1 stop and start bit
 *  			: No Parity
 *  Includes	: Uart3_Init to setup the Uart
 *  			: Uart3_Put to send an 8 bit value
 *  			: Uart3_Get to receive an 8 bit value
 */

#ifndef SOURCES_ADC1_H_
#define SOURCES_ADC1_H_

uint8_t adc1_out();
void adc1_init();

#endif /* SOURCES_ADC1_H_ */
