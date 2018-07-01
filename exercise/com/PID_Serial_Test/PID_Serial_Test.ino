
#include <AutoPID.h>

//pid settings and gains
#define PWM_MIN -1000
#define PWM_MAX 1000
#define KP .02
#define KI 0.012
#define KD 0.

double Set_val=1;

// pid val
double Pos, setPos, PWM;

AutoPID PID(&Pos, &setPos, &PWM, PWM_MIN, PWM_MAX, KP, KI, KD);

void setup()
{
  // BangBang = 50, Step = 100
  Set_PID(400,100);
  
  Serial.begin(57600);
}

void loop()
{
  if(Serial.available())
  {
    SetVal(Serial.parseFloat());
  }

  Set_val++;

  if(Set_val==200)
  {
    Set_val=1;
  }

  PID.run();
  Go_PID();
}

double SetVal(float Val)
{
  Set_val = (double)Val;
  Serial.println(Set_val);
  delay(1);
  
  return(Set_val);
}

void Set_PID(int Bang, int Step)
{
  PID.setBangBang(Bang);
  PID.setTimeStep(Step);

  return 0;
}

void Go_PID(void)
{
  setPos = Set_val;
  Pos += PWM;
  
  Serial.print("Pos : ");
  Serial.print(Pos);
  Serial.print("  setPos : ");
  Serial.print(setPos);
  Serial.print("  PWM : ");
  Serial.println(PWM);
}

