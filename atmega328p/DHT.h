#ifndef __DHT_H__
#define __DHT_H__

#include <stdio.h>
#include <avr/io.h>

//Port where DHT sensor is connected
#define DHT_DDR DDRB
#define DHT_PORT PORTB
#define DHT_PIN PINB0
#define DHT_INPUTPIN 0

//Define sensor type
#define DHT_DHT11 0
#define DHT_DHT22 1
#define DHT_TYPE 0

//timeout retries
#define DHT_TIMEOUT 200

//functions

extern int8_t dht_GetTempUtil(int8_t *temperature, int8_t *humidity);


#endif