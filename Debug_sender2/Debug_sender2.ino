// Arduino NANO
// Recive debug

#include "C:\Users\Administrator\Documents\GitHub\ArdunoNano-SoftwareSerial-Full-Duplex\SoftSerial\Serial.h"

SoftSerial mSerial;

void setup()
{
  Serial.begin(9600, SERIAL_8N1);
  mSerial.Begin(2, 3, 9600, SERIAL_7E1);
}

void loop() 
{
 mSerial.Write('S');
 mSerial.Write(13); //printlinebuffer
 Serial.write('S');
 Serial.write(13);
 delay(500);
}