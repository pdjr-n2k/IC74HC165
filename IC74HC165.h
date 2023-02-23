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

/**
 * @brief Interface for a 74HC165-based PISO buffer.
 * 
 * A buffer consists of one or more daisy-chained IC74HC165 ICs each of
 * which maintains an 8-bit status.
 * 
 * This library allows the hardware interface to a buffer to be
 * configured and initialised and allows the buffer to be interrogated
 * at the byte or bit level. 
 */
class IC74HC165 {

  public:

    /******************************************************************
     * @brief Construct a new IC74HC165 object
     * 
     * @param gpioClock - the GPIO pin connected to IC pin 2 (CP/clock).
     * @param gpioData - the GPIO pin connected to IC pin 9 (Q7/data).
     * @param gpioLatch - the GPIO pin connected to IC pin 1 (PL/latch).
     * @param bufferCount - the number of buffer ICs in the daisy-chain.
     */
    IC74HC165(uint8_t gpioClock, uint8_t gpioData, uint8_t gpioLatch, unsigned int bufferCount = 1);

    /******************************************************************
     * @brief Initialise the connection to the PISO buffer.
     * 
     * Set the I/O mode of the GPIO pins used to interface with the
     * buffer. Must be called from setup().
     */
     void begin();

    /******************************************************************
     * @brief Read data from the PISO buffer.
     * 
     * Returns the status of a the buffer as an array of status values
     * each element representing the status of a single buffer IC.
     *   
     * @return pointer to an array containing the status of all the
     * buffer ICs in the daisy-chain.  Element 0 relates to the first
     * IC in the chain, element 1 the second and so on.
     */
    uint8_t *read();

    /******************************************************************
     * @brief Get the value of a specified bit in the PISO buffer.
     * 
     * @param bit - the bit to be selected.
     * @return uint8_t - the state of the specified bit (0 or 1).
     */
    uint8_t readBit(unsigned int bit);

    /**
     * @brief Configure an automatic callback for handling buffer data.
     * 
     * This method configures a mechanism for invoking a callback
     * function at a regular interval and works in concert with
     * callbackMaybe().
     * 
     * Make a call to configureCallback() in setup() and make a call to
     * callbackMaybe() in loop().
     * 
     * @param callback - this function will be called with the status
     * of each IC in the buffer passed as an element in the array
     * passed as its sole argument.
     * @param callbackInterval - the interval in milliseconds between
     * successive invocations of the callback function (defaults to
     * 1s).
     */
    void configureCallback(void (*callback)(uint8_t *), unsigned long callbackInterval = 1000UL);
    
    /**
     * @brief Maybe invoke a configured callback.
     * 
     * This method should be called from loop() and if force is false
     * will determine when to invoke the callback function based upon
     * the specified update interval.
     * 
     * @param force - if true then invoke callback immediately
     * (defaults to false).
     */
    void callbackMaybe(bool force = false);


  private:
    uint8_t gpioClock;
    uint8_t gpioData;
    uint8_t gpioLatch;
    uint8_t *buffer;
    unsigned int bufferCount;

    void (*callback)(uint8_t *);
    unsigned long callbackInterval;
    
};

#endif