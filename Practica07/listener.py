#!/usr/bin/env python3
import rospy   """ Importamos la biblioteca rospy """
from std_msgs.msg import String  """ Importamos la biblioteca de String para los mensajes"""
def callback(data):   """ Llamamos la funcion que suscribe al topico para escuchar"""
    rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)
def listener():
    rospy.init_node('listener', anonymous = True) """Inicia el nodo en modo listener """
    rospy.Subscriber("chatter", String, callback) """ Se suscribe al topico chatter y va a escuchar un String"""
    rospy.spin() """empieza a funcionar hasta que reciba señal de shutdown"""
if __name__ == '__main__':   """condicion de salida"""
    listener() 
