#include <Wire.h>

float a = 0, b = 0;


void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

volatile int val_a; volatile int val_b; volatile int val;
volatile int hel_a; volatile int hel_b; volatile int hel;

void loop()
{

  // ~~ START Inquire value from SlaveID#11 ~~ //
  Wire.requestFrom(11, 4);
  while (Wire.available())
  {
    val_a = Wire.read(); val_b = Wire.read();
    val = (val_b << 8) | val_a;
    Serial.print("val:"); Serial.println(val);

    hel_a = Wire.read(); hel_b = Wire.read();
    hel = (hel_b << 8) | hel_a;
    Serial.print("hel:"); Serial.println(hel);
    Serial.println("");
  }
  delay(500);

  a = float(val)/100;
  b = float(hel)/100;

  Serial.println(a);
  Serial.println(b);
  
}
