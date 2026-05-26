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

byte current, previous1, previous2;
bool initialized;
bool isON;


void setup() {
  Serial.begin(9600, SERIAL_8N1);
  isON = false;

  mSerial.Begin(TX, RX, 9600, SERIAL_7E1);
  mSerial.Write(CmdCancelBuffer);
  mSerial.Write("READY");
  mSerial.Write(0x0D);
  mSerial.Write(0x0A);

  pinMode(CTS, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void Handshake_ON() {

    Serial.write(XON);
  
}
void Handshake_OFF() {

    Serial.write(XOFF);

  
}

void loop()
{
  Handshake_OFF();
  int count = Serial.available();

  if (count > 0)
  {
    Handshake_OFF();
    int count = 0;
    Serial.print("write bytes: ");
    Serial.println(count);

    while(Serial.available())
    {
      mSerial.Write(Serial.read());
    }
    delay(10);
  }
}




void loop1() {
  
  int count = 0;

  do {
    count = Serial.available();
    if (count>60) Handshake_OFF();

    //The thermal printer is busy, stop sending
    bool busy = digitalRead(CTS);
    digitalWrite(LED_BUILTIN, busy);
    
    if (busy) {
      Handshake_OFF();
      delay(100);
      continue;
    }

    if (count > 0) {
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
  } while (count);

  Handshake_ON();
}