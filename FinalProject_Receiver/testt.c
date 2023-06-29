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

int main ()
{

	GPIO_setupPinDirection(PORTA_ID,PIN3_ID ,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTA_ID,PIN4_ID ,PIN_OUTPUT);
	DcMotor_init();
	UART_init(MYUBRR);
	LCD_init();

      while(1)
       {
    	  int Temp_celsius=UART_recieveByte();
	      if (Temp_celsius >= 60)
	      {

		    GPIO_writePin(PORTA_ID,PIN3_ID,LOGIC_HIGH);
		    GPIO_writePin(PORTA_ID,PIN4_ID,LOGIC_HIGH);
		    LCD_displayStringRowColumn(0,3,"FAN IS ON ");
		   	LCD_displayStringRowColumn(1,3,"7areeeeaaaa");
		   	LCD_moveCursor(0,13);
		   	LCD_intgerToString(Temp_celsius);


	       }
     	else
     	   {
		    GPIO_writePin(PORTA_ID,PIN3_ID,LOGIC_LOW);
		    GPIO_writePin(PORTA_ID,PIN4_ID,LOGIC_LOW);
		    LCD_displayStringRowColumn(0,13,"  ");
		    LCD_displayStringRowColumn(0,3,"FAN IS OFF");
		    LCD_displayStringRowColumn(1,3,"Temp = ");

		    LCD_intgerToString(Temp_celsius);
		    LCD_displayString(" C");
		    _delay_ms(200);
	       }
        }


}





