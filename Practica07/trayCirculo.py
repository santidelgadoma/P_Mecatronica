#!/usr/bin/env python
# author : Sumanth Nethi
import rospy """importamos la libreria de rospyn para llamar a publisher"""
from geometry_msgs.msg import Twist """Libreria para asignar velocidades"""
import sys """Libreria para recibir parámetros"""


def turtle_circle(radius): """Inicio de la función para mover a la tortuga en circulo según un radio"""
	rospy.init_node('turtlesim', anonymous=True) """Iniciamos el nodo de la tortuga"""
	pub = rospy.Publisher('/turtle1/cmd_vel',
						Twist, queue_size=10) """Preparamos el publisher para asiganar las velocidades"""
	rate = rospy.Rate(10) """Rate de 10 para mover la simulación a ese ritmo"""
	vel = Twist() """Variable de seguridad"""
	"""Cuando se está activo, se mueve según un radio asiganado sobre el eje z con velocidad en x"""
	while not rospy.is_shutdown():
		vel.linear.x = radius
		vel.linear.y = 0
		vel.linear.z = 0
		vel.angular.x = 0
		vel.angular.y = 0
		vel.angular.z = 1
		rospy.loginfo("Radius = %f",
					radius) """Imprime el radio al que se mueve"""
		pub.publish(vel) """Publicamos al nodo la velocidad obtenida"""
		rate.sleep() """Apagamos momentaneamente el rate"""


if __name__ == '__main__': """Función que recibe los parámetros, en este caso el radio, y detecta errores, si no hay error, ejecuta el código"""
	try:
		turtle_circle(float(sys.argv[1]))
	except rospy.ROSInterruptException:
		pass


