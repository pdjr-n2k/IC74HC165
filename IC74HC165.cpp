/**********************************************************************
 * IC74HC165.cpp - ADT for accessing a 74HC165 PISO buffer.
 * 2022 (c) Paul Reeve <preeve@pdjr.eu>
 */

#include <cstddef>
#include <Arduino.h>
#include <IC74HC165.h>

IC74HC165::IC74HC165(uint8_t gpioClock, uint8_t gpioData, uint8_t gpioLatch) {
  this->gpioClock = gpioClock;
  this->gpioData = gpioData;
  this->gpioLatch = gpioLatch;
}

void IC74HC165::begin() {
  pinMode(this->gpioClock, OUTPUT);
  pinMode(this->gpioData, INPUT);
  pinMode(this->gpioLatch, OUTPUT);
}

uint8_t IC74HC165::readByte() {
  return((unsigned char) this->read());
}

unsigned int IC74HC165::read(unsigned int count) {
  unsigned int retval = 0;
  digitalWrite(this->gpioClock, 1);
  digitalWrite(this->gpioLatch, 1);
  while (count--) {
    retval = (retval << 8);
    retval |= shiftIn(this->gpioData, this->gpioClock, MSBFIRST);
  }
  digitalWrite(this->gpioLatch, 0);
  return(retval);
}

unsigned int IC74HC165::readBit(unsigned int bit) {
  return(bitRead(this->read((bit / 8) + 1), bit));
}
