# SoftSerial
Arduino SoftwareSerial in Full Duplex Rx/Tx

The code was needed to provide a second serial port to the **ArduinoNano** and then use the ***HardwareSerial0*** to communicate with the PC.
> **Limitation:** Only one instance of ***SoftSerial*** can be created.

Use Timer1 CompareA and CompareB interrupts to independently manage the write and read flow.

## Packet Functions
These functions create the byte data and the packet, and vice versa.
> static byte getdata(ushort packet, const byte bits, const byte parity, bool &valid);
> static ushort getpacket(const byte data, const byte bits, const byte parity, byte stop);
the streaming packet is the raw bits stream sent to interrupt functions
