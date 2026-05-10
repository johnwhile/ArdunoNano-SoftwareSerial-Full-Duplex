// Arduino MEGA 2560
// Send data with different speed

unsigned long previous;
unsigned long msdelay = 2;


void setup()
{
  Serial.begin(9600, SERIAL_8N1);
  Serial1.begin(9600, SERIAL_8N1);
  Serial2.begin(9600, SERIAL_8N1);
  Serial3.begin(9600, SERIAL_8N1);

  previous = millis();

  Serial.println("");
  Serial.println("SETUP");
}


int count = 0;


void loop() 
{
  for (int i=0;i<100;i++)
  {
    Serial1.write('a');
  }
  Serial1.write('\n');

}

void loop1() 
{
  Serial1.write('a');
  unsigned long current = millis();

  if (current - previous > msdelay)
  {
    count++;
    Serial2.write('b');
    previous = millis();
    if (count>32)
    {
      count = 0;
      Serial2.write('\n');
    }
  }
}