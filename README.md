# IC74HC165

ADT for accessing a 74HC165 PISO buffer.

The 74HC165 is an 8-bit parallel-to-serial I/O buffer. This library
allows the host application to read the buffer.

Example:
```
#define PisoDataGpio 2
#define PisoLatchGpio 3
#define PisoClockGpio 4
#define MyInterestingBit 6
 
IC74HC165 piso = IC74HC165(PisoDataGpio, PisoLatchGpio, PisoClockGpio);
 
void setup() {
  piso.begin();
}
 
void loop() {
  uint8_t byte;
  int bit;

  byte = piso.readByte();
  bit = piso.readBit(MyInterestingBit); 
}
```
