#include <ros.h>
#include <geometry_msgs/Twist.h>

#define echoPin 7
#define trigPin 6

long duration;
float distance;

ros::NodeHandle nh;

geometry_msgs::Twist velCommand;

ros::Publisher pub("turtle1/cmd_vel", &velCommand);

void setup(){
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  nh.initNode();
  nh.advertise(pub);
  
  velCommand.linear.x = 0.0;
  velCommand.linear.y = 0.0;
  velCommand.linear.z = 0.0;
  velCommand.angular.x = 0.0;
  velCommand.angular.y = 0.0;
  velCommand.angular.z = 0.0;
}

void loop(){
  Frena();
  pub.publish(&velCommand);
  nh.spinOnce();

}

void Frena(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0343/2;
  if(distance <= 15){
    velCommand.linear.x = 0.0;
    velCommand.linear.y = 0.0;
    velCommand.linear.z = 0.0;
    velCommand.angular.x = 0.0;
    velCommand.angular.y = 0.0;
    velCommand.angular.z = 0.0;
  }
  else{
    velCommand.linear.x = 2.0;
    velCommand.linear.y = 0.0;
    velCommand.linear.z = 0.0;
    velCommand.angular.x = 0.0;
    velCommand.angular.y = 0.0;
    velCommand.angular.z = 1.0;
  }

}
