/**********************************************************************
 * @file IC74HC165.h
 * @author Paul Reeve (preeve@pdjr.eu)
 * @brief Interface for the 74HC165 PISO buffer.
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
     * @param gpioClock - the GPIO pin connected to IC pin 2 (CP/clock).
     * @param gpioData  - the GPIO pin connected to IC pin 9 (Q7/data).
     * @param gpioLatch - the GPIO pin connected to IC pin 1 (PL/latch).
     */
    IC74HC165(uint8_t gpioClock, uint8_t gpioData, uint8_t gpioLatch);

    /******************************************************************
     * @brief Set the I/O mode of the configured GPIO pins.
     * 
     * In Arduino world this method should be called from setup(). 
     */
    void begin();

    /******************************************************************
     * @brief Convenience function to read data from a single connected
     * buffer (or the first buffer in a daisy-chain). 
     * 
     * @return uint8_t - the status of the buffer.
     */
    uint8_t readByte();

    /******************************************************************
     * @brief Read data from one or more buffers.
     * 
     * @param count - the number of buffers whose data should be read
     * (defaults to 1).
     * 
     * @return unsigned int - the status of the buffer(s). 
     */
    unsigned int read(unsigned int count = 1U);

    /******************************************************************
     * @brief Return the value of a specified bit from the connected
     * buffer(s).
     * 
     * @param bit - the bit to be selected.
     * @return int  - the state of the specified bit (0 or 1).
     */
    unsigned int readBit(unsigned int bit);

  private:
    uint8_t gpioClock;
    uint8_t gpioData;
    uint8_t gpioLatch;
};

#endif
