#include "fsl_device_registers.h"
#include "board.h"
#include "pin_mux.h"
#include "fsl_clock_manager.h"
#include "fsl_debug_console.h"
#include <stdio.h>

#define ATTR_NO_INSTRUMENT_FUNCTION __attribute__( ( no_instrument_function ) )
static inline ATTR_NO_INSTRUMENT_FUNCTION void nop( void )
{
__asm__ __volatile__ ("nop");
}
#include "UART3.c"
#include "ADC1.c"
#include "Shift_Reg.c"
#define number_of_row 64
//char state = 'A';
char state_col = 'A';
char state_row = 'A';
uint8_t data[64];
void SW2();
void SW2_INIT();
void SYSTEM_INIT();
void test_send(uint8_t value);
void test_recieve();
void blank_func();
void flow_ctrl_P();

void send_16(uint8_t *data);
int main(void)
{	int i=0;
	//uint8_t adc1out;
    SYSTEM_INIT();
	printf("Welcome\n\r");
	while(1)
	{
		for (i=0;i<number_of_row;i++)
		{
			next_row_col(&state_col,&state_row);
			//SW2();
			blank_func();
			data[i]=adc1_out();
			if(i%8 == 0)
			{printf("\r\n");}
			printf("%d\t",data[i]&0xFF);
			//SW2();
		}
		printf("\n\r");
//		{SW2();
//		GPIOB_PSOR|=0x400;
//		SW2();
//		GPIOB_PCOR|=0x400;
//		SW2();
//		GPIOB_PTOR|=0x8;
//		SW2();
//		GPIOB_PTOR|=0x8;
//		SW2();
//		GPIOB_PTOR |= 0x4;
//		SW2();
//		GPIOB_PTOR |= 0x4;}


		send_16(data);
		//SW2();
	}
}
void SYSTEM_INIT()
{
	SW2_INIT();
	Shift_Reg_Init();
	Uart3_Init();
	hardware_init();
    dbg_uart_init();
    adc1_init();

}
void SW2_INIT()
{	// Set up SW2 as input
	SIM_SCGC5   |=  0x800;    	// Gate PORTB 0x400 on Gate PORTC on 0x800
	PORTC_PCR6  &= ~(111<<8); 	// Clear Mux
	PORTC_PCR6  |=  (001<<8); 	// Set	Mux Alt 1
	GPIOC_PDDR  &= ~(1<<6);	  	// Set 	as input
}
void SW2()
{
	while ((GPIOC_PDIR &0x40) != 0){}
	while ((GPIOC_PDIR &0x40) == 0){}
}
void test_send(uint8_t value)
{
	uint8_t check=0;
	while (check != 'P')
	{
		check =Uart3_Get();
	}
	Uart3_Put(value);
	Uart3_Put('\n');
	Uart3_Put('\r');
}
void test_recieve()
{
	char buff [64];
	buff[0]=0;
	int count =0;
	while(buff[count-1] != '\r')
	{
		buff[count]=Uart3_Get();
		printf("%d is char \r\n",buff[count]&0xFF);
		count++;
	}
	int i;
	for (i=0;i<count;i++)
	{
		printf("%c",buff[i]);
	}
}
void blank_func()
{//steady 1 read at 200
	// okay at 170
 // bad at 150
int i;
	for (i=0;i<300;i++)
	{
		nop();

	}

}
void send_16(uint8_t *data)
{

	int i;
	flow_ctrl_P();
		for (i=0;i<64;i++)
		{
			//if(i%8==0)
			//{
			//	printf("\r\n");
			//}
			//printf("\t%d",data[i]&0xff);
			Uart3_Put(data[i]);

		}
}
/*EOF*/
void flow_ctrl_P()
{
	uint8_t check=0;
		while (check != 'P')
		{
			check =Uart3_Get();
		}

}
