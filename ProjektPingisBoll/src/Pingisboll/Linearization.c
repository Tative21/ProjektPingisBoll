/*
 * Linearization.c
 *
 * Created: 2016-05-09 18:47:20
 *  Author: William
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

int linearization(void){
	
	float result = 0;
	float avrunda = 0;
	float X =0;
	int i = 0;
	for (i = 0; i< 10;i++)
	{
		result=analogRead();
		
		avrunda=avrunda+result;
	}
	avrunda=avrunda/10;
	
	//printf("IR-sensor är: %d \n", avrunda);
	
	
	
	
	if ((avrunda>=2150) && (avrunda<2400))
	{
		X=2250;											// 15 cm
	}
	else if ((avrunda>=1950) && (avrunda<2150))
	{
		X= 2123;									    	// 20 cm
	}
	else if ((avrunda>=1570) && (avrunda<1950))
	{
		X=1996;											// 25 cm
	}
	else if ((avrunda>=1480) && (avrunda<1570))
	{
		X=1869;											// 30 cm
	}
	else if ((avrunda>=1380) && (avrunda<1480))
	{
		X=1780;											// 35 cm
	}
	else if ((avrunda>=1320) && (avrunda<1380))
	{
		X=1615;											// 40 cm
	}
	else if ((avrunda>=1280) && (avrunda<1320))
	{
		X=1488;											// 45 cm
	}
	else if ((avrunda>=0) && (avrunda<1280))
	{
		X=1361;											// 50 cm
	}
	
	return X;
}

int valueInCm(int value){
	int cm = 1;
	
	if (value == 15)
	{
		cm=2250;
	}
	else if (value == 20)
	{
		cm=2123;
	}
	else if (value == 25)
	{
		cm=1996;
	}
	else if (value == 30)
	{
		cm=1869;
	}
	else if (value == 35)
	{
		cm=1780;
	}
	else if (value == 40)
	{
		cm=1615;
	}
	else if (value == 45)
	{
		cm=1488;
	}
	else if (value == 50)
	{
		cm=1361;
	}
	return cm;
}

int returnCM(int value)
{
		if ((value>=2150) && (value<2400))
		{
			cm_value=15;											// 15 cm
		}
		else if ((value>=1950) && (value<2150))
		{
			cm_value= 20;									    	// 20 cm
		}
		else if ((value>=1570) && (value<1950))
		{
			cm_value=25;											// 25 cm
		}
		else if ((value>=1480) && (value<1570))
		{
			cm_value=30;											// 30 cm
		}
		else if ((value>=1380) && (value<1480))
		{
			cm_value=35;											// 35 cm
		}
		else if ((value>=1320) && (value<1380))
		{
			cm_value=40;											// 40 cm
		}
		else if ((value>=1280) && (value<1320))
		{
			cm_value=45;											// 45 cm
		}
		else if ((value>=0) && (value<1280))
		{
			cm_value=50;											// 50 cm
		}
		
		return cm_value;
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
			
// 			B_temp=B_value;
// 			Kp_temp=(Kp_value);
// 			Ti_temp=(Ti_value/100);
// 			Td_temp=(Td_value/100);
// 			dT_temp=(dT_value/100);
			
			setPIDvalues(B_value,Kp_value,Ti_value,Td_value,dT_value);
			}
		}



