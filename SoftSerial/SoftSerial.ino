#include "Serial.h"

SoftSerial mSerial;


void setup() {
  mSerial.Begin(2, 3, 9600, SERIAL_8N1);
  Serial.begin(9600, SERIAL_8N1);


}

void loop()
{
  Debug2();
}

void Debug1()
{
  if (Serial.available()>0)
  {
    mSerial.Write((byte)Serial.read());
  }
}
void Debug2()
{
  mSerial.Write("Sulaj Gay");
  mSerial.Write(13);
  delay(500);
}


void Debug3() 
{
  // optional: flush all wrinting byte
  while (mSerial.RequestToWrite())
    delay(mSerial.RequestToWrite() * mSerial.MilliSecondForByte);

  for (byte b = 0; b < 127; b++) {
    //optional: wait at least 10 free space in writing buffer
    while (mSerial.AvailableToWrite() < 10)
      delay(10 - mSerial.AvailableToWrite() * mSerial.MilliSecondForByte);

    mSerial.Write_Async(b);
  }
}