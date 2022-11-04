#!/usr/bin/env python3
import rospy """Importamos la libreria rospy para comunicación entre python y ROS"""
import sys """Librería para asignar parámetros de entrada"""
from geometry_msgs.msg import Twist """Librería para los movimientos y velocidades"""

"""Función para mover la tortuga en rectángulo"""
def turtle_rectangulo():
	largo = 4 """Asignamos el largo de nuestro rectangulo"""
	ancho = 2 """Asignamos el ancho de nuestro rectangulo"""
	rospy.init_node('turtle1', anonymous =True) """Iniciamos la comunicación con el nodo de ROS"""
	pub = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size=10) """ Publicamos en el archivo de velocidad de la tortuga el Twist"""
	rate = rospy.Rate(1) """Velociad de la simulación"""
	i = 1 """Iniciamos un contador"""
	vel = Twist() """Velocidad que pasaremos al nodo"""
	"""Al estar activo el programa..."""
	while not rospy.is_shutdown(): 
		if i%2 == 1: """ Si i modulo 2 es igual a 1, entonces pasa a este código"""
			"""Asignamos velocidad solo en x, respectivo al largo"""
			vel.linear.x = largo
			vel.linear.y = 0
			vel.linear.z = 0
			vel.angular.x= 0
			vel.angular.y = 0
			vel.angular.z = 0
			rospy.loginfo("Rectangulo") """Imprimimos Rectangulo"""
			pub.publish(vel) """Publicamos la velocidad"""
			i = i+1 """Aumentamos el contador"""
			rate.sleep() """Apagamos momentaneamente el rate"""
			largo = -1 * largo """Revertimos el sentido de la velocidad de derecha a izquierda y viceversa"""
		else:	"""Si i modulo 2 es igual a 0, entra a este código"""
			"""Asignamos velocidad solo en y, respectivo al ancho"""
			vel.linear.x = 0
			vel.linear.y = ancho
			vel.linear.z = 0
			vel.angular.x= 0
			vel.angular.y = 0
			vel.angular.z = 0
			rospy.loginfo("Rectangulo") """Imprimimos Rectangulo"""
			pub.publish(vel) """Publicamos la velocidad"""
			i = i+1 """Aumentamos el contador"""
			rate.sleep() """Apagamos momentaneamente el rate"""
			ancho = -1 * ancho """Revertimos el sentido de la velocidad de arriba a abajo y viceversa"""
	
	if __name__ == '__main__': """Se intenta hacer el código, que en este caso no ercibe parámetros, caso contrario, lanza el error"""
		try: 
			turtle_rectangulo()
	except rospy.ROSInterruptException:
		pass
