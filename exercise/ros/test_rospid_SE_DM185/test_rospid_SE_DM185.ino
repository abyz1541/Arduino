
#include <ros.h>
#include <std_msgs/Float64.h>

double con_val=0;

void call_pid_control(const std_msgs::Float64& control_val)
{
  con_val = control_val.data;
}

ros::NodeHandle nh;
std_msgs::Float64 set_point;

std_msgs::Float64 motor_state;
ros::Publisher pos_set("/SE_DM185/setpoint", &set_point);
ros::Publisher pos_state("/SE_DM185/state", &motor_state);
ros::Subscriber<std_msgs::Float64> control_effort_sub("/SE_DM185/control_effort", call_pid_control);
  
void setup()
{              
  nh.initNode();
  nh.advertise(pos_set);
  nh.advertise(pos_state);
  nh.subscribe(control_effort_sub);
  set_point.data=100;
}
 
void loop()
{
  motor_state.data += con_val;
  pos_set.publish(&set_point);
  pos_state.publish(&motor_state);

  if(motor_state.data==-100)
  {
    set_point.data = 100;
  }
  else if(motor_state.data==100)
  {
    set_point.data = -100;
  }

  

  nh.spinOnce();
}

