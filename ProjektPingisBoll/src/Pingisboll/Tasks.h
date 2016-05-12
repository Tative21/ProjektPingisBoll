/*
 * codeLock.h
 *
 * Created: 2015-12-17 19:21:20
 *  Author: William Ouda, Jack Mao
 */ 


#ifndef CODELOCK_H_
#define CODELOCK_H_

#include <asf.h>
#include <FreeRTOS.h>
#include "Tasks.h"
#include <task.h>

void setPIDvalues(uint8_t V_values, double Kp_values, double Ti_values, double Td_values, double dT_values);



#define TASK_CODELOCK_STACK_SIZE        (2048/sizeof(portSTACK_TYPE))
#define TASK_CODELOCK_STACK_PRIORITY    (2)
void task_codeLock(void *pvParameters);
void task_Led2(void *pvParameters);
int linearization(void);
int valueInCm(int value);
#define pinMode ioport_set_pin_dir
#define OUTPUT IOPORT_DIR_OUTPUT
#define INPUT IOPORT_DIR_INPUT
#define setPin ioport_set_pin_level
#define setPinA0 ioport_set_pin_mode
#define readPin ioport_get_pin_level
#define setPWM pwm_set_duty_cycle
#define Limitation 18500

#define pin3 PIO_PC28_IDX
#define pin4 PIO_PC26_IDX
#define pin5 PIO_PC25_IDX
#define pin6 PIO_PC24_IDX
#define pin7 PIO_PC23_IDX
#define pin8 PIO_PC22_IDX
#define pin12 PIO_PD8_IDX
#define pin9 PIO_PC21_IDX
#define pin10 PIO_PC29_IDX
#define setDAC dacc_write_conversion_data


#define B1 PIO_PD7_IDX
#define B2 PIO_PC24_IDX
#define B3 PIO_PC26_IDX
#define motor PIO_PB16_IDX
#define drive PIO_PB15_IDX
#define motor1 PIO_PB25_IDX
#define inputA0 PIO_PA16_IDX
#define inputA1 PIO_PA24_IDX


#endif /* CODELOCK_H_ */