// Inclusión de librerías necesarias para la comunicación con ROS 
#include <ros.h>
#include <std_msgs/Empty.h>

// Nodo de comunicación con ROS
ros::NodeHandle nh;

// Mensaje que será enviado a ROS
void messageCb( const std_msgs::Empty& toggle_msg){
  if(digitalRead(13) == 0){ // Si el led de la placa arduino está pagado lo encendemos 
    digitalWrite(13, HIGH);
   }
  else{ // Si el led de la placa arduino está predido se apaga, cada segundo se hace esta interacción 
    digitalWrite(13,LOW);
  }
}

// Realizamos la subscripción a ROS
ros::Subscriber<std_msgs::Empty> sub("toggle_led", &messageCb);


void setup(){
  pinMode(13, OUTPUT); // Definimos el pin 13 como salida 
  nh.initNode(); // iniciamos el nodo nh
  nh.subscribe(sub); // iniciamos la subscripción del nodo nh
}

void loop(){
  nh.spinOnce(); // Mantenemos la comunicación con el nodo de ROS
  delay(1000); // Retardo de 1 segundo 
}
