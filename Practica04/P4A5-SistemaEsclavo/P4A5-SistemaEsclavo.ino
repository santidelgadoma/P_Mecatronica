# include <Wire.h>   //Incluimos las librerias que nos permiten
# include <Servo.h>  // comunicarse con otro arduino (Wire)
                     // y para comunicarse con el Servo motor
int angulo;   //declaramos una varibale para guardar el dato que recibimos

Servo serv1;
void setup() {
  // put your setup code here, to run once

  Wire.begin(0xAF);  // Iniciamos la comunicación con el canal AF

  Wire.onReceive(lectura); //Al recibir un mensaje llamamos la funcion lectura

  serv1.attach(4);   // adherimos el Servo al puerto al que lo conectamos


  Serial.begin(9600);  //Establecemos la velocidad de la comunicación 
}

void loop() {
  // put your main code here, to run repeatedly:
 Serial.println(angulo); //Imprimimos el dato para comprobar
 delay(10);

}

void lectura(){
  angulo = Wire.read();  // Guardamos el dato leído en la variable angulo
  serv1.write(angulo);   // Le pasamos este dato al servo
  delay(10);
}
