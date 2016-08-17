/*
* 
*  Author: William Ouda, Zeid Bekli
*/
#include <asf.h>
#include <FreeRTOS.h>
#include "Pingisboll/Tasks.h"
#include <task.h>

#include "Pingisboll/io_uart.h"
#include "Pingisboll/adcFunctions.h"
#include "Pingisboll/io_pwm.h"
#include "Pingisboll/Linearization.h"
#include "Pingisboll/global.h"

int Utsignal =0;
int Felvarde =0;
int cm_value =0;

uint8_t BB=0;
double Kp=0;
double Ti=0;
double Td=0;
double dT=0;


uint8_t B_temp=0;
double Kp_temp=0;
double Ti_temp=0;
double Td_temp=0;
double dT_temp=0;

int linjer=0;


double Summa=0;

void task_codeLock(void *pvParameters)
{

	
	portTickType xLastWakeTime; //Last time the task was active.
	const portTickType xTimeIncrement = 100; //100 ms
	xLastWakeTime = xTaskGetTickCount();
	
	int k=0;
	float Borvarde;
	float test;
	
	pinMode (pin3, OUTPUT );
	pinMode (pin4, OUTPUT );
	pinMode (pin5, OUTPUT );
	pinMode (pin6, OUTPUT );
	pinMode (pin7, OUTPUT );
	pinMode (pin10, OUTPUT );
	pinMode (pin12, OUTPUT );
	pinMode (pin9, OUTPUT );
	pinMode (motor, OUTPUT );
	pinMode (drive, OUTPUT );
	pinMode(inputA0,INPUT);
	
	
	int SignalAvIr =0; 
	
	double differans=0;
	double P=0;
	double I=0;
	double D=0;
	int lastFelvarde = 0;
	

		
		
	while(1){
			
			setPin(pin9,0);
			setPin(pin12,1);	
			
		

		linjer=linearization(BB);
		
		SignalAvIr=linjer;

		Felvarde=SignalAvIr-BB;
		
		differans=(Felvarde-lastFelvarde);
		Summa = Summa + Felvarde;
		P=(Felvarde);
		I=(dT/Ti)*Summa;
		D=(Td/dT)*differans;
		
		
		Utsignal=Kp*(P+I+D);
		//Utsignal=Kp*P;
		
	
		lastFelvarde=Felvarde;
		if (Utsignal<1)
		{
			Utsignal=0;
		}
		if (Utsignal>100)
		{
			Utsignal=100;
		}
		//-----------------------------------------
		// testa sätt in max(min på utsignal så den inte går för högt upp bollen.
		//------------------------------------
		
		setPWM(Utsignal);

		
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); //Wait for the next cycle the task will be active.
	}
}



void task_Led2(void *pvParameters)
{
	char returned=0;
	int gg = 0;
	
	portTickType xLastWakeTime; //Last time the task was active.
	const portTickType xTimeIncrement = 100; //100 ms
	xLastWakeTime = xTaskGetTickCount();
	 
	//receive_Values();
	while(1){
		receive_Values();
		
			
		returned = uart_receive_char();
		
		if (returned == '1')
		{
		
			printf("%d \n",Utsignal);
		}
		
		if (returned == '2')
		{
			printf("%d \n",Felvarde);	
			
		}
		if (returned == '3')
		{
			printf("%d \n", linjer);
			
		}
		

		
//--------------------------------------------------------------------------
	
		//Receiver
	/*
			pinMode (pin3, OUTPUT );
			
			if (BB==57)
			{
				setPin(pin3,HIGH);
			}
			*/
	vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
	}
}

void setPIDvalues(uint8_t B_values, double Kp_values, double Ti_values, double Td_values, double dT_values){
	
	
	B_temp=B_values;
	Kp_temp=(Kp_values/100);
	Ti_temp=(Ti_values/100);
	Td_temp=(Td_values/100);
	dT_temp=(dT_values/100);
	
	BB=B_temp;
	Kp=Kp_temp;
	Ti=Ti_temp;
	Td=Td_temp;
	dT=dT_temp;
	
	}



