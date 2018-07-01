
#include <ros.h>
#include <std_msgs/Int16.h>
#include <math.h>
#include <sensor_msgs/JointState.h>

#define stp 13
#define dir 12

long go_step = 0;
float set_pos = 0;

void onestep_CW(long stp_num);
void onestep_CCW(long stp_num);
void pos_cal(float POS);
void call_stepmotor (const sensor_msgs::JointState& POS);

ros::NodeHandle nh;
ros::Subscriber<sensor_msgs::JointState> StepScr("/joint_states", call_stepmotor);
 
void setup() {                
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);

  nh.initNode();
  nh.subscribe(StepScr);
}
 
void loop() {
  nh.spinOnce();
  delay(100);
}

void call_stepmotor (const sensor_msgs::JointState& POS){
  
  float pos = degrees(POS.position[0]);
  delay(1000);
  pos_cal(pos);
  delay(1000);
  
  if(go_step > 0){

    onestep_CW(go_step);
    
  }else if(go_step < 0){

    onestep_CCW(-go_step);
    
  }
  delay(10);
  
}

void onestep_CW(long stp_num){
    digitalWrite(dir, LOW);
    delayMicroseconds(1000);

    for(int i=0 ; i < stp_num ; i++ ){
      
      digitalWrite(stp, HIGH);   
      delayMicroseconds(1000);               
      digitalWrite(stp, LOW);  
      delayMicroseconds(1000);
      
    }
}

void onestep_CCW(long stp_num){
    digitalWrite(dir, HIGH);
    delayMicroseconds(1000);
    
    for(int i=0 ; i < stp_num ; i++ ){
      
      digitalWrite(stp, HIGH);   
      delayMicroseconds(1000);               
      digitalWrite(stp, LOW);  
      delayMicroseconds(1000);
      
    }
  
}

void pos_cal(float POS){

  if(set_pos > 0 && POS > 0){

        go_step = (long)((set_pos - POS)/1.8);
        set_pos = POS;
        
  }else if(set_pos < 0 && POS > 0){

        go_step = (long)((POS - set_pos)/1.8);
        set_pos = POS;
    
  }else if(set_pos > 0 && POS < 0){

        go_step = (long)((POS - set_pos)/1.8);
        set_pos = POS;
    
  }else if(set_pos < 0 && POS < 0){

      if(set_pos > POS){
        
        go_step = (long)((POS - set_pos)/1.8);
        set_pos = POS;
        
      }else if(set_pos < POS){

        go_step = (long)((set_pos - POS)/1.8);
        set_pos = POS;
      }
  }

}

