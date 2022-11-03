#!/usr/bin/env python3
import rospy  """ importamos la bibiloteca de ros para python"""
from std_msgs.msg import String """ importamos la biblioteca de mensajes String"""
def talker():  """Llamamos la función que creara una publicacion a través de un nodo talker con un queue de 10 posiciones y transmitimos a una frecuencia de 1hz"""
    pub = rospy.Publisher('chatter', String, queu_size=10)
    rospy.init_node('talker', anonymous = True)
    rate = rospy.Rate(1)
    i = 0  """ iniciamos un contador para enumerar los mensajes"""
    while not rospy.is_shutdown():  """Iniciamos un loop para publicar el mensaje y frenar la comunicación con rate.sleep()"""
        hello_str= "hello world %s" % i
        rospy.loginfo(hello_str)
        pub.publish(hello_str)
        rate.sleep()
        i=i+1
if __name__ == '__main__':  """condicion de salida por si hay alguna interrupcion en el funcionamiento de ROS"""
    try:
        talker()
        except rospy.ROSInterruptExeption:
            pass
        
