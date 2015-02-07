/*
 * ir_sensor.c
 *
 *  Created on: Jan 29, 2015
 *      Author: Himanshu
 */

#include "../include/ir_sensor.h"
#include <system.h>
#define bit_flipper_base	(volatile int *)	BIT_FLIPPER_0_BASE
#define TOP_BOUND 370
#define BOT_BOUND 0

int init = 0;

int paddleposition(int *spi_read){

	//	all registers to zero
	if(init == 0){
		 *(bit_flipper_base)	=	0x00000;
		 init++;
	 }

	//Arbitrary Command MOSI
	 char spi_command_string_tx[10] = "$HELLOABC*";
	 alt_avalon_spi_command(SPI_BASE,0, 1, spi_command_string_tx, 1, spi_read, 0);
	 int input = (VOLT_CONV*((6787.00 / (*spi_read - 3.00) - 4.00 )- VOLT_OFF));

	 if(input>BOT_BOUND && input<TOP_BOUND)
		 *(bit_flipper_base+1) = 1;

	 return *(bit_flipper_base+1);
}
