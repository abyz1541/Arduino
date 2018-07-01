
// Arduino Mega

#include <ros.h>
#include <sensor_msgs/JointState.h>
#include <Wire.h>

float a,b,c;

void Set_Pos(const sensor_msgs::JointState& POS)
{
  a = degrees(POS.position[0]);
  b = degrees(POS.position[1]);
  c = degrees(POS.position[2]);
}

ros::NodeHandle NH;
ros::Subscriber<sensor_msgs::JointState> PWM_SCR_1("/joint_states", Set_Pos);

void setup()
{
  // Join i2c bus with address #11
  Wire.begin(11);      
  Wire.onRequest(requestEvent);      // register event

  NH.initNode();
  NH.subscribe(PWM_SCR_1);
}

void loop()
{
  NH.spinOnce();
  delay(1);
}

// Function that executes whenever data is requested by master
// This function is registered as an event, see setup()
void requestEvent()
{
  long val = (long)((a+180)*100);
  long hel = (long)((b+180)*100);
  long han = (long)((c+180)*100);
  
  Wire.write(val); // lower byte
  Wire.write(val>>8); // upper byte

  Wire.write(hel); // lower byte
  Wire.write(hel>>8); // upper byte

  Wire.write(han); // lower byte
  Wire.write(han>>8); // upper byte
}
