# IC74HC165

ADT for reading a 74HC165 parallel-in-serial-out (PISO) buffer.

## Constructor

### IC74HC165 *myPiso*(*gpioClock*, *gpioData*, *gpioLatch*);

```
IC74HC165 myPiso(10, 11, 12);
```
Create a new IC74HC165 instance *myPiso* for the PISO buffer IC
connected to the *gpioClock*, *gpioData* and *gpioLatch* pins.

## Methods

### begin()
```
myPiso.begin();
```
Configures the operating mode of the host microcontroller's GPIO pins
which are associated with this instance (the data pin is set to
INPUT_PULLUP, the other pins to OUTPUT).

### readByte()
```
uint8_t status = myPiso.readByte();
```
Returns a integer in the range 0..255 representing the current state of
the IC's parallel inputs (pins A..H map onto bits 0..7 of the returned
value).

### readBit(*bit*)
```
int state = myPiso.readBit(5);
```
Returns an integer value 0 or 1 representing the current state of the
IC's parallel input pin identified by *bit* (an integer value in the
range 0..7 mapping onto pins A..H).
