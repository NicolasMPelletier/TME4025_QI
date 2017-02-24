/*
 * Shift_Reg.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Nic
 */

#ifndef SOURCES_SHIFT_REG_H_
#define SOURCES_SHIFT_REG_H_

void off();
void Shift_Reg_Init();
void clk();
void strb();
void A();
void B();
void C();
void D();
void E();
void F();
void G();
void H();
void next(char state,char state_max);
void same(char *state,char state_max);
void next_row_col(char* state_col,char* state_row);
void next2(char *state,char state_max);

#endif /* SOURCES_SHIFT_REG_H_ */
