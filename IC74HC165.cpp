/**********************************************************************
 * @file IC74HC165.cpp
 * @author Paul Reeve (preeve@pdjr.eu)
 * @brief Interface for thw 74HC165 PISO buffer.
 * @version 0.1
 * @date 2023-02-08
 * @copyright Copyright (c) 2023
 */

#include <cstddef>
#include <Arduino.h>
#include <IC74HC165.h>

IC74HC165::IC74HC165(uint8_t gpioClock, uint8_t gpioData, uint8_t gpioLatch, unsigned int buffers) {
  this->gpioClock = gpioClock;
  this->gpioData = gpioData;
  this->gpioLatch = gpioLatch;
  this->buffers = buffers;

  this->callback = 0;
  this->callbackInterval = 0UL;
}

void IC74HC165::begin() {
  pinMode(this->gpioClock, OUTPUT);
  pinMode(this->gpioData, INPUT);
  pinMode(this->gpioLatch, OUTPUT);
}

unsigned int IC74HC165::read() {
  unsigned int state = 0;
  digitalWrite(this->gpioClock, 1);
  digitalWrite(this->gpioLatch, 1);
  for (unsigned int i = 0; i < this->buffers; i++) {
    state << 8;
    state |= shiftIn(this->gpioData, this->gpioClock, MSBFIRST);  
  }
  digitalWrite(this->gpioLatch, 0);
  return(state);
}

void IC74HC165::configureCallback(void (*callback)(unsigned int status), unsigned long callbackInterval) {
  this->callback = callback;
  this->callbackInterval = callbackInterval;
}
    
void IC74HC165::callbackMaybe(bool force) {
  static unsigned long deadline = 0UL;
  unsigned long now = millis();
  unsigned int status;

  if (this->callback) {
    if (((this->callbackInterval) && (now > deadline)) || force) {
      status = this->read();
      this->callback(status);
      deadline = (now + this->callbackInterval);
    }
  }
}
