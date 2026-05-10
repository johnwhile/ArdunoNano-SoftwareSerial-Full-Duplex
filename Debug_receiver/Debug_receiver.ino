// Arduino NANO
// Recive debug

#include "C:\Users\johnw\Projects\ArdunoNano-SoftwareSerial-Full-Duplex\SoftSerial\Serial.h"

SoftSerial mSerial;

void setup()
{
  Serial.begin(9600, SERIAL_8N1);
  mSerial.Begin(2, 3);

  Serial.println("");
  Serial.println("SETUP RX");
}



void loop() 
{
  if (mSerial.AvailableToRead())
  {
    Serial.write(mSerial.Read());
  }
}