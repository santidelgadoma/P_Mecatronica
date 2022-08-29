#define pot A0  //definimos pot como la entrada de lectura analógica
#define led 13  //definimos un led como salida del puerto 13
float value = 0; //inicializamos una variable para guardar la lectura analógica
float brillo; // inicializamos una variable que usaremos para guardar un cálculo

int pwm = 0; // inicializamos una variable en la que guardaremos un cálculo

void setup() {
  // No definimos pinMode porque directamennte leeremos una entrada analógica
  pinMode(led, OUTPUT);
  Serial.begin(9600); // establecemos la velocidad de la comunicación entre computadora y microcontrolador

}

void loop() {
  value = analogRead(pot) ; // leemos la entrada analógica
  pwm = value/4; // sacamos el valor pwm
  
  analogWrite(led, pwm); //asignamos lo obtenido como parametro de la salida led
  
  brillo = value/1023*100; // convertimos a voltaje para establecer el brillo 
  Serial.print("Brillo: "); // imprimimos lo calculado en la terminal
  Serial.println(brillo);
  delay(0); // Ponemos un delay de 0 para que no se detecte el cambio entre estados del led y fluya

}
