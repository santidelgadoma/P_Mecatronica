#define trigPin 7
#define echoPin 6   //Definimos los pines que usaremos del microcontrolador
#define led 8
long duracion;    //Definimos las variables con las que leeremos los valores y transformarlos
int distancia;


void setup() {
pinMode(trigPin,OUTPUT);   //Definimos los pines de salida digital y la velocidad de la comunicacion
pinMode(echoPin,INPUT);
pinMode(led, OUTPUT);

Serial.begin(9600);
}

void loop() {
digitalWrite(trigPin, LOW);   //Mandamos una señal a traves del trigger con un delay de 10 macrosegundos antes de apagarlo
delayMicroseconds(2);

digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duracion = pulseIn(echoPin, HIGH);   //Leemos en el pin de echo la señal y calculamos la duracion de la señal para luego calcular la distancia al objeto
distancia = duracion * 0.0343 / 2;

Serial.print("Distancia: "); //Imprimimos el valor de distancia obtenido
Serial.print(distancia);
Serial.println(" cm");

if(distancia <= 15) {   //Configuramos un led que se encienda cuando hay un objeto a 15 cm de distancia o menos
  digitalWrite(led, HIGH);
}
else {
  digitalWrite(led, LOW);
}
}
