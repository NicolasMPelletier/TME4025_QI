#ifndef UART3_H_
#define UART3_H_

void Uart3_Init();				// Sets up Pins C16 Rx and C17 Tx
void Uart3_Put(uint8_t SEND);	// Send 8 bits
uint8_t Uart3_Get();			// Get 8 bits

#endif // UART3_H_
