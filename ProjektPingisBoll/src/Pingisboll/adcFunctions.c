/*
 * adcFunctions.c
 *
 *  Author: William Ouda & Zeid Bekli
 */ 

#include <inttypes.h>
#include <asf.h>
#include "Pingisboll/adcFunctions.h"


// Skapar inställningar för ADC.

int analogInit(int pinNumber)
{
	/* 
	 * The pin number is the analog input pin on the DUe board, see http://www.arduino.cc/en/Hacking/PinMappingSAM3X
	 * Obviously it starts at analog 0 which is equivalent to the analog input on PA16
	 * so you need to figure out which AD channel this corresponds to
	 *
	 * See code example http://asf.atmel.com/docs/latest/sam.drivers.adc.adc_example.arduino_due_x/html/sam_adc_quickstart.html
	 * It is assumed that the AD-converter is using 12 bits
	 */
	
	
	pmc_enable_periph_clk(ID_ADC);	/* power the clock for the ADC with pmc_enable_periph_clk(ID_ADC) */
	adc_init(ADC,sysclk_get_main_hz(),1000000,8); 		
	adc_configure_timing(ADC,0,ADC_SETTLING_TIME_3,1);
	adc_set_resolution(ADC,ADC_MR_LOWRES_BITS_12);	
		
	adc_enable_channel(ADC,ADC_CHANNEL_7);
	//adc_enable_channel(ADC,ADC_CHANNEL_6);
	adc_configure_trigger(ADC,ADC_TRIG_SW,0);				
	
	
	return 0;	/* if everything is ok */
}


// returnera det nuvarande värdet.

uint32_t analogRead(void)
{
	adc_start(ADC);
	//delay_us(100);
	//delayMicroseconds(100);
	
	return adc_get_channel_value(ADC,ADC_CHANNEL_7);
	/* Replace with actual value read from A/D input*/
}

//uint32_t analogRead1(int pinNumber)
//{
	/*
	adc_start(ADC);

	return adc_get_channel_value(ADC,ADC_CHANNEL_6);
	/* Replace with actual value read from A/D input*/
	
//}
	
	
