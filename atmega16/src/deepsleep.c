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
#define LED PB0


volatile uint8_t WDT_flag = 0; // initilize watch dog timer flag

void WDT_interrupt_enable(void)
{
    //WDTCR |= (1<<WDTOE)|(1<<WDE); // change enable
    WDTCR = (1<<WDE)|(1<<WDP2)|(1<<WDP1)|(1<<WDP0); // config interrup with 2 sec timeout
}

void WDT_sysreset_enable(void)
{
    WDTCR = (1<<WDE)|(1<<WDP2)|(1<<WDP1)|(1<<WDP0); // config interrup with 2 sec timeou
}

void WDT_interrupt_disable(void)
{
    WDTCR |= (1<<WDTOE);//clear
    WDTCR &= ~(1<<WDE); // clear
    
}

void interrupt_wait(void)
{
    WDT_flag = 0;
    WDT_interrupt_disable();
    //PORTB ^= (1<<LED);
    while (!WDT_flag);
}

int main()
{
    ADCSRA &= ~(1<<ADEN);// disable ADC
    //MCUCR |= (3<<5);
    //MCUCR = (MCUCR &~(1<<5))|(1<<6);
    DDRB &= ~(1<<LED); // set PB0 as output
    //PORTB |= (1<<LED);


    WDT_interrupt_enable();

    sei(); // enable interrupt

    while(1)
    {
        

       set_sleep_mode(SLEEP_MODE_PWR_DOWN);
       sleep_mode();
       interrupt_wait();
 
       
       
        
       
    }

    return 0;
}

ISR(WDT_vect)
{
    WDT_interrupt_disable();
	WDT_flag = 1;
    PORTB &= ~(1<<LED);
}
