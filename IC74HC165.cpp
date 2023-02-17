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

IC74HC165::IC74HC165(uint8_t gpioClock, uint8_t gpioData, uint8_t gpioLatch) {
  this->gpioClock = gpioClock;
  this->gpioData = gpioData;
  this->gpioLatch = gpioLatch;
  this->callback = 0;
  this->updateInterval = 0UL;
  this->callbackCount = 0U;
}

void IC74HC165::begin() {
  pinMode(this->gpioClock, OUTPUT);
  pinMode(this->gpioData, INPUT);
  pinMode(this->gpioLatch, OUTPUT);
}

uint8_t IC74HC165::read(unsigned int buffer) {
  uint8_t retval;

  digitalWrite(this->gpioClock, 1);
  digitalWrite(this->gpioLatch, 1);
  for (unsigned int i = 0; i <= buffer; i++) {
    retval = shiftIn(this->gpioData, this->gpioClock, MSBFIRST);  
  }
  digitalWrite(this->gpioLatch, 0);
  return(retval);
}

unsigned int IC74HC165::readBit(unsigned int bit) {
  return(bitRead(this->read(bit / 8), (bit % 8)));
}

void IC74HC165::configureCallback(void (*callback)(uint8_t *), unsigned long updateInterval, unsigned int callbackCount) {
  this->callback = callback;
  this->updateInterval = updateInterval;
  this->callbackCount = callbackCount;
}
    
void IC74HC165::callbackMaybe(bool force) {
  static uint8_t *buffer = new uint8_t[this->callbackCount - 1];
  static unsigned long deadline = 0UL;
  unsigned long now = millis();

  if (this->callback) {
    if (((this->updateInterval) && (now > deadline)) || force) {
      for (unsigned int i = 0; i < this->callbackCount; i++) buffer[i] = this->read(i);
      this->callback(buffer);
      deadline = (now + this->updateInterval);
    }
  }
}
