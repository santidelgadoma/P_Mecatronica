#define pot A0   // definimos el componente pot como el lector analógico
#define led 13.  // definimos la salide led en el puerto 13
float value = 0; // definimos un valor float llamado value para guardar la lectura analógica
float voltaje;   // definimos un valor float llamado voltaje que usaremos para imprimir la variacion del voltaje
void setup() {

  pinMode(led, OUTPUT); // definimos el pinMode
  Serial.begin(9600);  // indicamos la velocidad de comunicacion entre el microcontrolador y la computadora

}

void loop() {
  value = analogRead(pot) ; // usamos la función analogRead para medir la información analógica
  voltaje = (value/1023*5); // calculamos el voltaje usando una regla de tres
  Serial.print("Voltaje: "); //imprimimos en una terminal la lectura obtenida
  Serial.print(voltaje);
  Serial.println("V");
  delay(100); // programamos un retardo de 1 segundo por lectura

  if (voltaje > 3) {.  // con este enunciado dividimos los voltajes entre menores a 3 y mayores a 3
    digitalWrite(led, HIGH); // si la lectura de voltaje es mayor a 3 entonces se prende el led
  }

  else{
    digitalWrite(led, LOW); // si la lectura de voltaje es menor a 3 entonces se apaga el led
  }

}
