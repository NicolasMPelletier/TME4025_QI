* Shift_Reg.c
 *
 *  Created on: Jan 15, 2017
 *      Author: Nic
 */

#include "fsl_device_registers.h"
#include "board.h"
#include "pin_mux.h"

#include "Shift_Reg.h"

void Shift_Reg_Init()
{
	SIM_SCGC5   |=  0x400;    	// Gate PORTB 0x400 on Gate PORTC on 0x800

	PORTC_PCR6  &= ~(111<<8); 	//Clear Mux
	PORTC_PCR6  |=  (001<<8); 	//Set	Mux Alt 1

	PORTB_PCR2  &= ~(111<<8); 	//Clear Mux
	PORTB_PCR2  |=  (001<<8); 	//Set 	Mux Alt 1
	PORTB_PCR3  &= ~(111<<8); 	//Clear Mux
	PORTB_PCR3  |=  (001<<8); 	//Set 	Mux Alt 1
	PORTB_PCR10 &= ~(111<<8); 	//Clear Mux
	PORTB_PCR10 |=  (001<<8); 	//Set 	Mux Alt 1
	GPIOB_PDDR  |= 0x40C;	  	//Set 	Pins 2,3,10 as output

	GPIOB_PCOR  |= 0x40C;		//Set Output to 0
}
void clk()
{	// Toggle Clock pin2
	//printf("clk in\n\r");
	//SW();
	GPIOB_PTOR |= 0x4;
	//SW();
	GPIOB_PTOR |= 0x4;
}
void strb()
{	// Toggle Strobe pin3
	//SW();
	GPIOB_PTOR|=0x8;
	//SW();
	GPIOB_PTOR|=0x8;
}
void off()
{	//0001
	GPIOB_PCOR|=0x400;
	clk();
	clk();
	clk();
	GPIOB_PSOR|=0x400;
	clk();
}
void A()
{	//0000
	GPIOB_PCOR|=0x400;
	clk();
	clk();
	clk();
	clk();
}
void B()
{	//0010
	GPIOB_PCOR|=0x400;
	clk();
	clk();
	GPIOB_PSOR|=0x400;
	clk();
	GPIOB_PCOR|=0x400;
	clk();
}
void C()
{	//0100
	GPIOB_PCOR|=0x400;
	clk();
	GPIOB_PSOR|=0x400;
	clk();
	GPIOB_PCOR|=0x400;
	clk();
	clk();
}
void D()
{	//0110
	GPIOB_PCOR|=0x400;
	clk();
	GPIOB_PSOR|=0x400;
	clk();
	clk();
	GPIOB_PCOR|=0x400;
	clk();
}
void E()
{	//1000
	GPIOB_PSOR|=0x400;
	clk();
	GPIOB_PCOR|=0x400;
	clk();
	clk();
	clk();
}
void F()
{	//1010
	GPIOB_PSOR|=0x400;
	clk();
	GPIOB_PCOR|=0x400;
	clk();
	GPIOB_PSOR|=0x400;
	clk();
	GPIOB_PCOR|=0x400;
	clk();
}
void G()
{	//1100
	GPIOB_PSOR|=0x400;
	clk();
	clk();
	GPIOB_PCOR|=0x400;
	clk();
	clk();
}
void H()
{	//1110
	GPIOB_PSOR|=0x400;
	clk();
	clk();
	clk();
	GPIOB_PCOR|=0x400;
	clk();
}
void next(char state,char state_max){
	switch (state){
	case 'A':
		off();
		A();
		state='B';
	break;
	case 'B':
		off();
		B();
		state='C';
	break;
	case 'C':
		off();
		C();
		state='D';
	break;
	case 'D':
		off();
		D();
		state='E';
	break;
	case 'E':
		off();
		E();
		state='F';
	break;
	case 'F':
		off();
		F();
		state='G';
	break;
	case 'G':
		off();
		G();
		state='H';
	break;
	case 'H':
		off();
		H();
		state='A';
		//printf("\n\r");
	break;
	}
	if(state>state_max)
	{
		state='A';
	}

	strb();
}


void next2(char *state,char state_max){
	switch (*state){
	case 'A':
		A();
		*state='B';
	break;
	case 'B':
		B();
		*state='C';
	break;
	case 'C':
		C();
		*state='D';
	break;
	case 'D':
		D();
		*state='E';
	break;
	case 'E':
		E();
		*state='F';
	break;
	case 'F':
		F();
		*state='G';
	break;
	case 'G':
		G();
		*state='H';
	break;
	case 'H':
		H();
		*state='A';
	break;
	}
	if(*state>state_max)
	{
		*state='A';
	}
}
void next_row_col(char* state_col,char* state_row)
{
	char state_max = 'H';

	if (*state_col==state_max)
	{
		next2(state_col,state_max);
		next2(state_row,state_max);
	}
	else
	{
		next2(state_col,state_max);
		same(state_row,state_max);
	}
	strb();
}

void same(char *state,char state_max){
	switch (*state){
	case 'A':
		A();
	break;
	case 'B':
		B();
	break;
	case 'C':
		C();
	break;
	case 'D':
		D();
	break;
	case 'E':
		E();
	break;
	case 'F':
		F();
	break;
	case 'G':
		G();
	break;
	case 'H':
		H();
	break;
	}
}

