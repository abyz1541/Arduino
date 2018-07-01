
#define ENB 11
#define IN3 12
#define IN4 13

const byte encoder0pinA = 2;//A pin -> the interrupt pin 0
const byte encoder0pinB = 3;//B pin -> the interrupt pin 1
byte encoder0PinALast;
int duration;//the number of the pulses
boolean Direction;//the rotation direction 

volatile int lastEncoded = 0;
volatile long encoderValue = 0;
 
void setup()
{  
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(57600);//Initialize the serial port
  EncoderInit();//Initialize the module
}
 
void loop()
{
  Serial.print("encoderValue:");
  Serial.println(encoderValue);
  encoderValue = 0;
  GoMotor(300, 0);
  delay(1000);
}


void GoMotor(double PWM, boolean DIRECTION)
{
  analogWrite(ENB,PWM);
  
  if(DIRECTION == 0)
  {
   digitalWrite(IN3, HIGH);
   digitalWrite(IN4, LOW); 
  }
  else
  {
   digitalWrite(IN3, LOW);
   digitalWrite(IN4, HIGH);
  }
}

// 5초 1회전 344
void GoMotor_test(double ENCODERVAL, boolean DIRECTION)
{
  ENCODERVAL = encoderValue;
  
  if(DIRECTION == 0)
  {
   digitalWrite(IN3, HIGH);
   digitalWrite(IN4, LOW); 
  }
  else
  {
   digitalWrite(IN3, LOW);
   digitalWrite(IN4, HIGH);
  }

  for (float i=0 ; i <= ENCODERVAL ; i++)
  {
    analogWrite(ENB,i);
  }
}
 
void EncoderInit()
{
  Direction = true;//default -> Forward  
  pinMode(encoder0pinA,INPUT); 
  pinMode(encoder0pinB,INPUT);
  digitalWrite(encoder0pinA, HIGH); //turn pullup resistor on
  digitalWrite(encoder0pinB, HIGH); //turn pullup resistor on
  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);
}
 

void updateEncoder(){
  int MSB = digitalRead(encoder0pinA); //MSB = most significant bit
  int LSB = digitalRead(encoder0pinB); //LSB = least significant bit
 
  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value
 
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;
 
  lastEncoded = encoded; //store this value for next time
}

