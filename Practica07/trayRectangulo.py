#!/usr/bin/env python3
import rospy
import sys
from geometry_msgs.msg import Twist

def turtle_rectangulo():
	largo = 4
	ancho = 2
	rospy.init_node('turtle1', anonymous =True)
	pub = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size=10)
	rate = rospy.Rate(1)
	i = 1
	vel = Twist()
	while not rospy.is_shutdown(): 
		if i%2 == 1:
			vel.linear.x = largo
			vel.linear.y = 0
			vel.linear.z = 0
			vel.angular.x= 0
			vel.angular.y = 0
			vel.angular.z = 0
			rospy.loginfo("Rectangulo")
			pub.publish(vel)
			i = i+1
			rate.sleep()
			largo = -1 * largo
		else:	
			vel.linear.x = 0
			vel.linear.y = ancho
			vel.linear.z = 0
			vel.angular.x= 0
			vel.angular.y = 0
			vel.angular.z = 0
			rospy.loginfo("Rectangulo")
			pub.publish(vel)
			i = i+1
			rate.sleep()
			ancho = -1 * ancho
	
	if __name__ == '__main__':
		try: 
			turtle_rectangulo()
	except rospy.ROSInterruptException:
		pass
