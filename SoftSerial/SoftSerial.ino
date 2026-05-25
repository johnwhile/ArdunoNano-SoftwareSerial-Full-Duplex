#include "Serial.h"

SoftSerial mSerial;

#define TX 2
#define RX 3
#define CTS 4
#define CmdESC 0x1B
#define CmdTrasmitNextChar 0x73
#define CmdCancelBuffer 0x07

void setup() {
  Serial.begin(9600, SERIAL_8N1);
  mSerial.Begin(TX, RX, 9600, SERIAL_7E1);
  
  mSerial.Write(CmdCancelBuffer);
  mSerial.Write("READY");
  mSerial.Write(0x0D);
  mSerial.Write(0x0A);
  
  pinMode(CTS, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

byte command[] = { 0, 0, 0 };
bool initialized;


void loop() {
  
  bool busy = digitalRead(CTS);
  digitalWrite(LED_BUILTIN, busy);
  
  if (busy) 
  {
    delay(10);
    return;
  }
  if (Serial.available()) 
  {
    command[2] = Serial.read();

    if (command[0] == CmdESC && command[1] == CmdTrasmitNextChar) {
      mSerial.End();
      mSerial.Begin(TX, RX, 9600, command[2]);
      if (mSerial.Initialized) 
      {
        mSerial.Write('#');
        mSerial.Write(CmdCancelBuffer);
      }
      command[0] = command[1] = command[2] = 0;
    } 
    else {
      command[0] = command[1];
      command[1] = command[2];

      if (mSerial.Initialized) mSerial.Write(command[2]);
    }
  }
}


void Debug() {
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