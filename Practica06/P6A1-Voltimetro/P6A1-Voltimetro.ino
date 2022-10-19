#define pot A0    //Definimos los pines que utilizaremos
#define led 7

float voltaje;   //Definimos las variables donde guardaremos las lecturas y luego transformarlas
float aux;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);   //Definimos el pin de salida digital asi como la velocidad de la comunicacion

}

void loop() {
  // put your main code here, to run repeatedly
  voltaje = analogRead(pot);   //Leemos el voltaje que recibe el pin y configuramos que si baja de 651 bits se va a la funcion emergencia
  if(voltaje < 651.0 ){
    emergencia();
  }
  else{
    digitalWrite(led,HIGH); //si el voltaje es mayor hacemos un parpadeo del led para mostrar que esta funcionando
    delay(250);
    digitalWrite(led, LOW);
    delay(250);
    Serial.println("Funcionando");
  }
  Serial.println(voltaje);
  

}


void emergencia(){
    digitalWrite(led, HIGH);  //Si se llama esta función emergencia el led se queda prendido informando que el voltaje es bajo
}
