/**********************************************************************
 * @file IC74HC165.h
 * @author Paul Reeve (preeve@pdjr.eu)
 * @brief Abstract interface to a 74HC165 PISO integrated circuit.
 * @version 0.1
 * @date 2023-02-06
 * @copyright Copyright (c) 2023
 */

#ifndef IC74HC165_H
#define IC74HC165_H

class IC74HC165 {

  public:

    /******************************************************************
     * @brief Construct a new IC74HC165 object
     * 
     * @param gpioClock - the GPIO pin connected to the CK pin.
     * @param gpioData  - the GPIO pin connected to the Q7 pin.
     * @param gpioLatch - the GPIO pin connected to the LT pin.
     */
    IC74HC165(uint8_t gpioClock, uint8_t gpioData, uint8_t gpioLatch);

    /******************************************************************
     * @brief Call from setup() to initialise the GPIO interface. 
     */
    void begin();

    /******************************************************************
     * @brief Convenience function to read data from a single buffer. 
     * 
     * @return uint8_t - the status of the buffer.
     */
    uint8_t readByte();

    /******************************************************************
     * @brief Read data from one or multiple (daisy-chained) buffers.
     * 
     * @param count - the number of buffers (defaults to 1).
     * @return unsigned int - the status of the buffer. 
     */
    unsigned int read(unsigned int count = 1);

    /******************************************************************
     * @brief Read one or multiple (daisy-chained) buffers and return
     * the value of a specified bit.
     * 
     * @param bit - the bit to be selected.
     * @return int  - the state of the bit (0 or 1).
     */
    unsigned int readBit(unsigned int bit);

  private:
    uint8_t gpioClock;
    uint8_t gpioData;
    uint8_t gpioLatch;
};

#endif
