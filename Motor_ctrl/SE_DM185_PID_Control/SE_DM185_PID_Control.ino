
#include <AutoPID.h>

// dc motor driver pin
#define ENB 11
#define IN3 12
#define IN4 13

//pid settings and gains
#define PWM_MIN 500
#define PWM_MAX 500
#define KP 10.
#define KI 0.02
#define KD 0.1

// pid val
double Pos, setPos, PWM;

//encoder 
const int encoderPinA = 2;    //A pin -> the interrupt pin 0
const int encoderPinB = 3;    //B pin -> the interrupt pin 1
double encoderPos = 0;

AutoPID PID(&Pos, &setPos, &PWM, PWM_MIN, PWM_MAX, KP, KI, KD);

void doEncoderA(){  encoderPos += (digitalRead(encoderPinA)==digitalRead(encoderPinB))?1:-1;}
void doEncoderB(){  encoderPos += (digitalRead(encoderPinA)==digitalRead(encoderPinB))?-1:1;}

const float ratio = 360./30./52.; // (각도/감속비/1회전당펄스수)

void setup()
{
  // 핀설정 및 초기화
  EncoderInit();
  MotorDriverInit();

  // PID 설정
  // 에러값이 200이상일때 min or max
  PID.setBangBang(200);
  // 10ms 마다 업데이트
  PID.setTimeStep(10);
  
  Serial.begin(57600);

  setPos = 300;

}

void loop()
{
  Pos = (double)(encoderPos*ratio);
  PID.run();

  doMotor(PWM)  ;
  
  Serial.print("Pos : ");
  Serial.print(Pos);
  Serial.print("  setPos : ");
  Serial.print(setPos);
  Serial.print("  PWM : ");
  Serial.println(PWM);

  delay(1);
}

void EncoderInit()
{
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(0, doEncoderA, CHANGE);
  attachInterrupt(1, doEncoderB, CHANGE);
}

void MotorDriverInit()
{
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void doMotor(double pwm)
{
  if(pwm <= 0)
  {
   digitalWrite(IN3, LOW);
   digitalWrite(IN4, HIGH); 
  }
  else
  {
   digitalWrite(IN3, HIGH);
   digitalWrite(IN4, LOW);
  }
  
  analogWrite(ENB,pwm);
}

