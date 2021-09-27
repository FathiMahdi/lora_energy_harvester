#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/delay.h>
#define LED PB0

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

void setup() {
  // put your setup code here, to run once:
  DDRB |= (1<<LED); //set PB0 as output
  // disable BOD
  MCUCR |= (3<<5);
  MCUCR = (MCUCR & ~(1<<5))|(1<<6);
  // disable ADC 
  ADCSRA &= (1<<7);
  sei(); // enable interrupt
  WDT_interrupt_enable();

}

void loop() {
  // put your main code here, to run repeatedly:
  PORTB |= (1<<LED);
  _delay_ms(1000);
  PORTB &= ~(1<<LED);
  MCUCR |= (3<<5);
  MCUCR = (MCUCR & ~(1<<5))|(1<<6);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_mode();
  interrupt_wait();

}

ISR(WDT_vect)
{
	WDT_flag = 1;
}
