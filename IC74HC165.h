/**********************************************************************
 * IC74HC165.h - ADT for accessing a 74HC165 PISO buffer.
 * 2022 (c) Paul Reeve <preeve@pdjr.eu>
 */

#ifndef IC74HC165_H
#define IC74HC165_H

class IC74HC165 {
  public:
    IC74HC165(uint8_t gpioClock, uint8_t gpioData, uint8_t gpioLatch);
    void begin();
    uint8_t readByte();
    int readBit(int bit);
  private:
    uint8_t gpioClock;
    uint8_t gpioData;
    uint8_t gpioLatch;
};

#endif
