
//Código para el maestro
# include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600); // Iniciamos la comunicacion a 9600 baudios. 
 
}

void loop() {
  for (int i=0; i<2; i++){ //ciclo para realizar esto en dos ocasiones, cambiando el contenido de i entre 0 y 1.
    Wire.beginTransmission(0xAF); // Inicia la comunicación con el sistema esclavo y la clave de comunicación es "0xAF"
    Wire.write(i); // Escribe en el sistema el contenido de i
    Wire.endTransmission(); // Termina la transmision
    Serial.println(i); // Imprime el mismo contenido que se envió. 
    delay(500); // Retardo de medio segundo.
  }
}
