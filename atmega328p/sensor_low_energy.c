/////////////////////////////////////////////
// Makefile for avr ave/gcc dudde          //
// 25/Sep/2021                             //
// made by FATHI MAHDI (_*_*_*_)           //
/////////////////////////////////////////////

#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <avr/wdt.h>
#include "DHT.h" //library that works with DHT sensor
//#include "DHT.h" //library that works with DHT sensor
#define LED PD7


uint8_t temperature_int = 0;
uint8_t humidity_int = 0;
volatile uint8_t WDT_flag = 0; // initilize watch dog timer flag

void WDT_interrupt_enable(void)
{
    WDTCSR |= (1<<WDCE)|(1<<WDE); // change enable
    WDTCSR = (1<<WDE)|(1<<WDP3)|(1<<WDP0); // config interrup with 2 sec timeout
}

void interrupt_wait(void)
{
    WDT_flag = 0;
    while (!WDT_flag);
}

int main()
{   
    DDRD |= (1<<LED); // led indicator for temperature
    ADCSRA &= ~(1<<7);// disable ADC
    MCUCR |= (3<<5);
    MCUCR = (MCUCR & ~(1<<5))|(1<<6);
    WDT_interrupt_enable();
    sei(); // enable interrupt

    while(1)
    {     
       dht_GetTempUtil(&temperature_int, &humidity_int);
       if (temperature_int >= 38)
       {
           PORTD |= (1<<LED); // high temp
       }
       else if(temperature_int < 38)
       {
           PORTD &= ~(1<<LED); // low temp
       }
       
       set_sleep_mode(SLEEP_MODE_PWR_DOWN);
       sleep_mode();
       interrupt_wait();    
    }

    return 0;
}

ISR(WDT_vect)
{
	WDT_flag = 1;
}
