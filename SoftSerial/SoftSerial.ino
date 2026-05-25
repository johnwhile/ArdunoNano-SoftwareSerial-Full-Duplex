#include "Serial.h"

SoftSerial mSerial;

#define TX 2
#define RX 3
#define CTS 4

const byte CmdESC = 27;
const byte CmdTrasmitNextChar = 115;
const byte CmdCancelBuffer = 7;
const byte XOFF = 19;
const byte XON = 17;


void setup() {
  Serial.begin(9600, SERIAL_8N1);
  Serial.write(XON);

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

  //Handshake XOnXOff. Serial receive buffer holds 64 bytes
  int count = Serial.available();
  if (count > 60) Serial.write(XOFF);
  if (count == 0) Serial.write(XON);

  //The thermal printer is busy, stop sending
  bool busy = digitalRead(CTS);
  digitalWrite(LED_BUILTIN, busy);

  if (!busy & count) 
  {
    command[2] = Serial.read();
    if (command[0] == CmdESC && command[1] == CmdTrasmitNextChar) {
      mSerial.End();
      mSerial.Begin(TX, RX, 9600, command[2]);
      if (mSerial.Initialized) {
        mSerial.Write('#');
        mSerial.Write(CmdCancelBuffer);
      }
      command[0] = command[1] = command[2] = 0;
    } else {
      command[0] = command[1];
      command[1] = command[2];

      if (mSerial.Initialized) mSerial.Write(command[2]);
    }
  }
  else 
  {
    delay(10);
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