# IC74HC165

ADT for accessing a 74HC165 parallel-in-serial-out (PISO) buffer.

## Constructor

```
IC74HC165 myPiso(*gpioClock*, *gpioData*, *gpioLatch*);
```
Create a new IC74HC165 instance for the PISO buffer IC connected to the
specified GPIO pins.

## Methods

### begin()
```
myPiso.begin();
```
Call from setup() to configure the operating mode of the GPIO pins (the
data pin is set to INPUT_PULLUP, the other pins to OUTPUT).

### readByte()
```
uint8_t status = myPiso.readByte();
```
Read the current state of the IC's parallel inputs int *status*.

### readBit(*bit*)
```
int state = readBit(*bit*);
```
Read into *state* the current value of the IC's parallel input pin
identified by *bit* (an integer value in the range 0..7).
