/**********************************************************************
 * @file IC74HC165.h
 * @author Paul Reeve (preeve@pdjr.eu)
 * @brief Interface for a 74HC165-based PISO buffer.
 * @version 0.1
 * @date 2023-02-06
 * @copyright Copyright (c) 2023
 */

#ifndef IC74HC165_H
#define IC74HC165_H

/**
 * @brief ADT representing a 74HC165-based serial input buffer.
 * 
 * A buffer consists of one or more daisy-chained IC74HC165 ICs each of
 * which maintains an 8-bit status byte which reflects the state of its
 * parallel inputs.
 * 
 * This library allows the hardware interface to a buffer to be
 * configured and initialised and allows the buffer to be interrogated
 * at the byte or bit level. 
 */
class IC74HC165 {

  public:

    /******************************************************************
     * @brief Create a new IC74HC165 object.
     * 
     * @param gpioClock - the GPIO pin connected to IC pin 2 (CP/clock).
     * @param gpioData - the GPIO pin connected to IC pin 9 (Q7/data).
     * @param gpioLatch - the GPIO pin connected to IC pin 1 (PL/latch).
     * @param buffers - the number of buffer ICs in the daisy-chain (optiomal: defaults to one).
     */
    IC74HC165(uint8_t gpioClock, uint8_t gpioData, uint8_t gpioLatch, unsigned int buffers = 1);

    /******************************************************************
     * @brief Initialise connection to the PISO buffer.
     * 
     * Sets the I/O mode of the GPIO pins used to interface with the
     * buffer and initialises the buffer from the current hardware
     * state.
     */
     void begin();

    /******************************************************************
     * @brief Read the buffer's current state.
     * 
     * @return integer representing the current buffer state.
     */
    unsigned int read();

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
     * @param callback - this function will be called with the current an array
     * containing the status bytes of each IC in the buffer
     * daisy-chain.
     * @param callbackInterval - the interval in milliseconds between
     * successive invocations of the callback function (defaults to
     * 1s).
     */
    void configureCallback(void (*callback)(unsigned int status), unsigned long callbackInterval = 1000UL);
    
    /**
     * @brief Maybe invoke the configured callback.
     * 
     * This method should be called from loop() and, if force is false,
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
    unsigned int buffers;

    void (*callback)(uint8_t *);
    unsigned long callbackInterval;
    
};

#endif