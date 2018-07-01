#include <Wire.h>

#define Slave 0x04

byte count = 0;

void setup()
{
  Wire.begin();
  Wire.onRequest(han);
}
void loop()
{
  
}

void han()
{
  Wire.write(count);
}

