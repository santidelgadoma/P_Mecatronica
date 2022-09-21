
# include <Wire.h>

#define led 13 // Puerto 13 asociado a un led

int dato; //variable entera para recibir el dato de la comunicacion 

void setup() {
  Wire.begin(0xAF); // Empieza comunicacion usando la clave acordada (0xAF)
  Wire.onReceive(lectura); // Determina que va a recibir informacion por medio de la funcion lectura
  pinMode(led,OUTPUT); // Define el pin 13 como salida 
  Serial.begin(9600); // Comunicacion a 9600 baudios 
}

void loop() {
  Serial.println(dato); // Imprime el dato obtenido desde el sistema maestro
  delay(100); // Retardo de .1 seg.

}

void lectura() {
  dato = Wire.read(); // Asigna a la variable dato previamente definida el contenido de leer lo que envia el sistema maestro
  if (dato == 1) { // condicional 
    digitalWrite(led,HIGH); // Si llega a este punto, prende el led
  }
  else {
    digitalWrite(led,LOW); // Si el dato no es 1 (que en este caso entonces sería 0), el foco se apaga.
  }
}
