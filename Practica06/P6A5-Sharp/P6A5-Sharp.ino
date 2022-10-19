// Codigo para medir distancia con el sharp
// El sharp mide con presicion distancias entre 10 y 80 cm. no tiene un comportamiento lineal, por lo que tenemos que hacer una caracterizacion de como mide

//definimos los pines que vamos a usar 
#define entrada A0
#define led 8
int distancia;    //Definimos las variables con las que guardaremos las lecturas asi como el valor que interpretaremos
int valor;

void setup() {
  //Comenzamos la comunicacion serial a 9600 baudios
  pinMode(led, OUTPUT);  //Definimos el pin de salida para iluminar el led
  Serial.begin(9600);
}

void loop() {
  //Lectura analògica del valor 
  valor = analogRead(A0);
  distancia = 0.002 * pow(valor,2) - 0.7143 * valor + 73.059;   //Implementamos la formula que obtuvimos de los valores medidos del sensor
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  if(distancia <= 15) {   //configuramos la salida del led para que se encienda cuando haya un obstaculo a 15 cm de distancia o menos 
    digitalWrite(led, HIGH);
    //Serial.println("Obstaculo");
  } else {
    digitalWrite(led, LOW);   //El led se mantiene apagado si no detecta la presencia
  }
  
  delay(50);
}
