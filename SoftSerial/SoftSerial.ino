#include "Serial.h"

SoftSerial mSerial;

#define TX 2
#define RX 3
#define CTS 4
#define CmdESC 0x1B
#define CmdTrasmitNextChar 0x73

void setup() 
{
  Serial.begin(9600, SERIAL_8N1);
}

byte command[]= {0, 0, 0};
bool initialized;

void loop()
{
  if (Serial.available())
  {
    command[2] = Serial.read(); 
    
    if (command[0] == CmdESC && command[1] == CmdTrasmitNextChar)
    {
        mSerial.End();
        mSerial.Begin(TX, RX, 9600, command[2]);
    }

    command[0] = command[1];
    command[1] = command[2];

    if (mSerial.Initialized) mSerial.Write(command[2]);
  }




}


void Debug() 
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