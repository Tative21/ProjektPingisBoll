/**
 * Author: William Ouda, Zeid Bekli
 *
 *
 *\file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "Pingisboll/Tasks.h"

#include <FreeRTOS.h>
#include <consoleFunctions.h>
#include "Pingisboll/io_uart.h"
#include "Pingisboll/adcFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pingisboll/io_pwm.h"
#include "Pingisboll/global.h"
#include "Pingisboll/Linearization.h"



int main (void)
{
	

		/* Initialise the Due board */
		sysclk_init();
		board_init();
		
		
		configureConsole();
		analogInit(0);
		pwm_setup();
		
		
		

		/* Create the first task for running the code lock */
		if (xTaskCreate(task_codeLock, (const signed char * const) "codeLock", TASK_CODELOCK_STACK_SIZE, NULL, 1, NULL) != pdPASS) {
			printf("Failed to create code lock task\r\n");
		}

		if (xTaskCreate(task_Led2, (const signed char * const) "Led2", TASK_CODELOCK_STACK_SIZE, NULL, 2, NULL) != pdPASS) {
			printf("Failed to create test led task\r\n");
		}
		/* Start the FreeRTOS scheduler running all tasks indefinitely*/
		vTaskStartScheduler();

		/* The program should only end up here if there isn’t enough memory to create the idle task */
	
}
