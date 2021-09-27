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
#include <avr/wdt.h>
#define LED PD7


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
    ADCSRA &= ~(1<<7);// disable ADC
    MCUCR |= (3<<5);
    MCUCR = (MCUCR & ~(1<<5))|(1<<6);
    DDRD |= (1<<LED); // set PD7 as output
    WDT_interrupt_enable();
    sei(); // enable interrupt

    while(1)
    {     
       PORTD |= (1<<LED);
       _delay_ms(1000);
       PORTD &= ~(1<<LED);
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
