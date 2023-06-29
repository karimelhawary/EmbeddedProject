/*
 * testt.c
 *
 *  Created on: Jun 18, 2023
 *      Author: hp
 */

#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"
#include "ADC.h"
#include "temp.h"
#include "lcd.h"
#include "motor.h"
#include "uart.h"

#define FOSC 1000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

int main()
{
	DcMotor_init();
	UART_init(MYUBRR);
	float Temp_sensor;
	const ADC_ConfigType Conv;
	float Temp_celsius;
	ADC_init(&Conv);

	while(1)
	{
		Temp_sensor = read_ADC(0);     //channel zero
		Temp_celsius = get_temp(Temp_sensor);

	    if(Temp_celsius >= 60)
            {
	    	UART_sendByte(Temp_celsius);
	    	DcMotor_RotateClockWise();

            }
	    else
	        {
	    	UART_sendByte(Temp_celsius);
	    	DcMotor_TurnOff();
	        }

	}

}







