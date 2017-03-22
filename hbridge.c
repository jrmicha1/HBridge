/*
Author: Joe Michaels
Assignment 3 H Bridge
Date Complete: 2/17/17
SER 486 
*/
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define BUTTON 0
#define ISRDelay 100

volatile int t = 0;
volatile int pinFlag = 1;
volatile int pin = 4;

void ISR(void);
		
int main(void)
{
  //gcc -Wall -o hbridge3 hbridge.c -lwiringPi

  wiringPiSetup();
	
  //GPIO pins 23, 24
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);

  
  if (wiringPiISR(BUTTON, INT_EDGE_RISING, &ISR) < 0)
  {
    printf("unable to setup ISR.\n");
  }else
  {
    printf("ISR setup complete.\n");
  }
  
  while(1)
  {
    digitalWrite (pin, HIGH);
  }
	
  return 0;
}

void ISR(void)
{
  if(millis() - t >= ISRDelay)//software debounce
  {
    t = millis();
    digitalWrite (pin, LOW);//close transistor gate
    
    pin = (pinFlag)? 5:4;
    pinFlag = (pinFlag)? 0:1;
    
    printf("ISR triggered: %d.\n",pin); 
  }
}
