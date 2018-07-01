
int photo = 2;

void setup()
{
  
  Serial.begin(9600);
  pinMode(photo, INPUT_PULLUP);
  attachInterrupt(photo, han, FALLING);

}

void loop() {

}

void han()
{
  Serial.println("han");
}

