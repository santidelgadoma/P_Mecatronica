#include <Servo.h> // incluimos la biblioteca que corresponde al servo motor

#define pot A0 // definir la entrada pot para recibir la señal analógica


float value = 0; // inicalizamos la variable value para guardar la lectura analógica
int angulo; // inicializamos la variable ángulo para calcular los movimientos del servo motor

Servo servo1; // instanciamos un servo

void setup() {
  servo1.attach(13); // anclamos el servo a el puerto 13
  Serial.begin(9600); // estabblecemos la velocidad de la comunicación entre la computadora y el microcontrolador
}

void loop() {

  value = analogRead(pot); // guardamos las lecturas analogicas en la variable value
  angulo = map(value,0,1023,0,180); // definimos los parametros con los que se medira el angulo para los movimientos
  servo1.write(angulo); // pasamos el valor calculado en angulo para mover el servo motor dependiendo de la lectura analógica
  delay(100); // aplicamos un delay para que no se mueva todo el tiempo el servo motor

}
