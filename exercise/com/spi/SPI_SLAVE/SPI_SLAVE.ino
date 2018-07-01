// Wire Master Reader
// I2C Protocol

#include <Wire.h>

float a = 50.11;
float b = 50.39;


void setup()
{
  // Join i2c bus with address #11
  Wire.begin(11);      
  Wire.onRequest(requestEvent);      // register event
}

void loop()
{
  delay(500);

}

// Function that executes whenever data is requested by master
// This function is registered as an event, see setup()
void requestEvent()
{
  int val = a*100;
  int hel = b*100;
  
  Wire.write(val); // lower byte
  Wire.write(val>>8); // upper byte

  Wire.write(hel); // lower byte
  Wire.write(hel>>8); // upper byte
}
