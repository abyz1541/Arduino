
#include <ros.h>
#include <Servo.h>
#include <sensor_msgs/JointState.h>

#define stp 13
#define dir 12
#define svo 11

Servo myservo;

void call_stepmotor (const sensor_msgs::JointState& POS);
void go_step(float pos);
void go_servo(float pos);

int step_state_1;
int step_state_2;
float servo_state_1;
float servo_state_2;

ros::NodeHandle nh;
ros::Subscriber<sensor_msgs::JointState> StepScr("/joint_states", call_stepmotor);

void setup() {                
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);

  myservo.attach(svo);
  
  step_state_1 = 0;
  step_state_2 = 0;
  servo_state_1 = 0;
  servo_state_2 = 0;

  nh.initNode();
  nh.subscribe(StepScr);
}
 
void loop() {
  nh.spinOnce();
  delay(1);
}

void call_stepmotor (const sensor_msgs::JointState& POS){
  
    float pos_0 = (float)POS.position[0];
    float pos_1 = (float)POS.position[1];

    go_step(pos_0);
    go_servo(pos_1);
}

void go_step(float pos){

  pos = degrees(pos);
  step_state_1 = (int)(pos/1.8);
  
  while(step_state_1 != step_state_2 ){

    if(step_state_1 > 0 && step_state_2 > 0){
        
        if(step_state_1 > step_state_2){
          digitalWrite(dir, HIGH);

          int step_val = step_state_1 - step_state_2;

          for(int i=0 ; i < step_val ; i++){
           digitalWrite(stp, HIGH);   
           delayMicroseconds(1000);               
           digitalWrite(stp, LOW);  
           delayMicroseconds(1000); 
          }
          
        }else{
          digitalWrite(dir, LOW);

          int step_val = step_state_2 - step_state_1;

          for(int i=0 ; i < step_val ; i++){
           digitalWrite(stp, HIGH);   
           delayMicroseconds(1000);               
           digitalWrite(stp, LOW);  
           delayMicroseconds(1000); 
          }
        }
    }else if(step_state_1 < 0 && step_state_2 < 0){
        if(step_state_1 > step_state_2){
            digitalWrite(dir, HIGH);
  
            int step_val = step_state_1 - step_state_2;
  
            for(int i=0 ; i < step_val ; i++){
             digitalWrite(stp, HIGH);   
             delayMicroseconds(1000);               
             digitalWrite(stp, LOW);  
             delayMicroseconds(1000); 
            }
            
          }else{
            digitalWrite(dir, LOW);
  
            int step_val = step_state_2 - step_state_1;
  
            for(int i=0 ; i < step_val ; i++){
             digitalWrite(stp, HIGH);   
             delayMicroseconds(1000);               
             digitalWrite(stp, LOW);  
             delayMicroseconds(1000); 
            }
          }
    }else if(step_state_1 >= 0 && step_state_2 <= 0){
      digitalWrite(dir, HIGH);
  
      int step_val = step_state_1 - step_state_2;
  
      for(int i=0 ; i < step_val ; i++){
        digitalWrite(stp, HIGH);   
        delayMicroseconds(1000);               
        digitalWrite(stp, LOW);  
        delayMicroseconds(1000);
      }
    }else if(step_state_1 <= 0 && step_state_2 >= 0){
      digitalWrite(dir, LOW);
  
      int step_val = step_state_2 - step_state_1;
  
      for(int i=0 ; i < step_val ; i++){
        digitalWrite(stp, HIGH);   
        delayMicroseconds(1000);               
        digitalWrite(stp, LOW);  
        delayMicroseconds(1000);
      }  
    }

    step_state_2 = step_state_1;

    if(step_state_1==step_state_2){
      break;
    }
  }
  delay(1);
}

void go_servo(float pos){

   pos = degrees(pos);
   servo_state_1 = pos+88;

   while(servo_state_1 != servo_state_2 ){

    myservo.write(servo_state_1);
    delay(30);
 
    step_state_2 = step_state_1;

    if(step_state_1==step_state_2){
      break;
    }
  }
  
}

