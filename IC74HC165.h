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
 * A PISO buffer can be built from one or more daisy-chained IC74HC165
 * ICs and can thus support multiple parallel inputs with each IC
 * supporting exactly eight input channels.
 * 
 */
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
     * @brief Initialise the connection to the PISO buffer.
     * 
     * Set the I/O mode of the GPIO pins used to interface with the
     * buffer. Must be called from setup().
     */
     void begin();

    /******************************************************************
     * @brief Read data from the PISO buffer.
     * 
     * Returns the status of a selected single IC in the buffer. Each
     * IC is addressed by its ordinal number in the daisy chain, with
     * the first IC having address 0.
     *   
     * @param buffer - the ordinal number of the IC whose status should
     * be returned (0 specifies the first IC).
     * 
     * @return unsigned char status recovered from the specified IC or
     * undefined if the IC selection address was invalid.
     */
    unsigned char read(unsigned int buffer = 0U);

    /******************************************************************
     * @brief Get the value of a specified bit in the PISO buffer.
     * 
     * @param bit - the bit to be selected.
     * @return int  - the state of the specified bit (0 or 1).
     */
    unsigned int readBit(unsigned int bit);

    /**
     * @brief Configure an automatic callback for handling buffer data.
     * 
     * This method configures a mechanism for invoking a callback
     * function at a regular interfval and works in concert with
     * callbackMaybe().
     * 
     * Make a call to configureCallback() in setup() and make a call to
     * callbackMaybe() in loop().
     * 
     * @param callback - this function will be called with the current
     * buffer status as its sole argument.
     * @param updateInterval - the interval in milliseconds between
     * successive invocations of the callback function (defaults to
     * 1s).
     * @param callbackCount - the number of buffer bytes to be included
     * in the status value passed to the callback function (defaults to
     * one byte).
     */
    void configureCallback(void (*callback)(unsigned int), unsigned long updateInterval = 1000UL, unsigned int callbackCount = 1U);
    
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
    void (*callback)(unsigned int);
    unsigned long updateInterval;
    unsigned int callbackCount;
    
};

#endif
