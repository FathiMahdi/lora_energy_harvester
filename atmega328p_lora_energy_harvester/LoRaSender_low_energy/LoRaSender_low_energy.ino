#define F_CPU 1000000UL
#include <SPI.h>
#include <LoRa.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/delay.h>

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
void setup() 
{
  //disable BOD
  MCUCR |= (3<<5);
  MCUCR = (MCUCR & ~(1<<5))|(1<<6);
  // disable ADC 
  ADCSRA &= ~(1<<7);
  sei(); // enable interrupt
  WDT_interrupt_enable();
  
  //Serial.begin(9600);
  //while (!Serial);

  //Serial.println("LoRa Sender");

  if (!LoRa.begin(915E6)) 
  {
    //Serial.println("Starting LoRa failed!");
      while (1);
  }
}

void loop() 
{
  //Serial.print("Sending packet: ");
  //Serial.println(counter);
  
  LoRa.beginPacket();
  LoRa.print("TES ");
  LoRa.endPacket();
  LoRa.idle();
  LoRa.sleep();
  LoRa.end();
  //MCUCR |= (3<<5);
  //MCUCR = (MCUCR & ~(1<<5))|(1<<6);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_mode();
  interrupt_wait();

}

ISR(WDT_vect)
{
  WDT_flag = 1;
}
