#define pot A0     //Definimos los pines que utilizaremos
#define led 13
 
float pwm;  //Definimos la variable para guardar la lectura y una para mapear el pwm
float value;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);   //Configurmaos  la comunicacion y el pin de salida digital para el led
  pinMode(led, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(pot);   //Leemos el valor de la entrada analogica
  Serial.println(value);
  pwm = map(value, 369, 1015, 255, 0); //Lo mapeamos para que este en pwm los valores 
  Serial.println(pwm);
  digitalWrite(led, pwm);   //Segun la luminosidad prenderemos el led con el valor equivalente
  
}
