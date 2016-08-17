/*
 * Linearization.c
 *
 * 
 *  Author: William, Zeid
 */ 
#include "Pingisboll/adcFunctions.h"
#include <asf.h>
#include "Pingisboll/global.h"
#include "Pingisboll/io_uart.h"
#include "Pingisboll/Tasks.h"


		uint8_t B_value=0;
		uint8_t Kp_value=0;
		uint8_t Ti_value=0;
		uint8_t Td_value=0;
		uint8_t dT_value=0;

uint8_t buf[4];
int loop =0;

int linearization(int bb){
	
	float result = 0;
	float avrunda = 0;
	int X =0;
	int i = 0;
	
	float y;
	for (i = 0; i< 10;i++)
	{
		result=analogRead();
		
		avrunda=avrunda+result;
	}
	float avrunda2=avrunda/10;
	
	if (bb>35){
	y=((-0.0918 * avrunda2)+148.46);	
	}
	
	if (bb<=35 && bb>=20 ){
	y=((-0.0655 * avrunda2)+113.32);
	}
		if (bb<20 ){
			y=((-0.0058 * avrunda2)+27.736);
		}
	

	
	X=y;
	return X;
}

void receive_Values(void){
		while (loop < 6)
		{
		
		for (loop ; loop<6; loop++)
		{   
			buf[loop] = uart_receive_char();
			delay_ms(500);
			}
		
			B_value=buf[1];
			Kp_value=buf[2];
			Ti_value=buf[3];
			Td_value=buf[4];
			dT_value=buf[5];
			

			
			setPIDvalues(B_value,Kp_value,Ti_value,Td_value,dT_value);
			}
		}



