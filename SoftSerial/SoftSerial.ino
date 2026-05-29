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


bool sended = false;
byte current, previous1, previous2;



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

void Handshake_ON() {
  if (sended) return;
  Serial.write(0);
  sended = true;
}

void Handshake_OFF() {
  sended = false;
}

void loop() {
  while (Serial.available()) {
    Handshake_OFF();

    //The thermal printer is busy, stop sending
    bool busy = digitalRead(CTS);
    digitalWrite(LED_BUILTIN, busy);

    if (busy) continue;

    byte current = Serial.read();
    if (current == CmdESC && previous1 == CmdTrasmitNextChar) {
      mSerial.End();
      mSerial.Begin(TX, RX, 9600, current);
      {
        mSerial.Write('#');
        mSerial.Write(CmdCancelBuffer);
      }
      current = previous1 = previous2 = 0;
    } else {
      previous2 = previous1;
      previous1 = current;
    }
    mSerial.Write(current);
  }
  Handshake_ON();
  delay(100);
}