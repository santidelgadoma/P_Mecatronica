// Ejercicio 6 - Pràctica 06
#include <LiquidCrystal_I2C.h>      //Incluimos la libreria para comunicarnos por I2C con el LCD
LiquidCrystal_I2C lcd(0x27,16,2);

# include "DHT.h"           //Incluimos la libreria correspondiente a el DHT

# define DHTPIN 18
# define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);    //Le asignamos el dht al pin que escogimos




#define lum A2      //Definimos los pines que se utilizaran
#define pot A4
#define led 5

#define trigPin 6
#define echoPin 7

float voltaje;   //Definimos las variables donde guardaremos las lecturas y transformaciones de estas
float aux;

bool alertaVoltaje = false;
bool alertaTemp = false; 
bool alertaDU = false;
bool alertaDS = false; 

int valueLum;
float pwm;
float tempAmbiente = 20; 


long duracion;
int distancia;

int distanciaSharp;
int valor;
float tempC;
String auxi;

void setup() {         //Definimos los pines de salida digital e iniciamos el lcd y el dht
  lcd.init();
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(led, OUTPUT);
  dht.begin();
}

void loop() {
  lcd.backlight();
  // voltaje
  voltaje = analogRead(pot);   //Hacemos la lectura del voltaje que le llega al sistema
  if(voltaje < 651 ){         //Configuramos la alerta para cuando el voltaje baje del voltaje requerido
    alertaVoltaje = true;
  } else {
    alertaVoltaje = false;
  }

  // Luminosidad   
  valueLum = analogRead(lum);    //Hacemos la lectura de la luminosidad que detecta el fotoresistor
  pwm = map(valueLum, 369, 1015, 255, 0);   //Sabiendo ya los valores que entrega hacemos el mapeo 

  // Temperatura
  tempC = dht.readTemperature();   //Leemos la temperatura del sensor dht

  if(tempC >= tempAmbiente + 5) {  //Configuramos el indicador de calor del sistema para anunciar si se sobrecalienta
    alertaTemp = true;
  }else {
    alertaTemp = false;
  }

  // Distancia con  ultrasònico
  digitalWrite(trigPin, LOW);     //Hacemos el envío y recepción del pulso ultrasonico
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duracion = pulseIn(echoPin, HIGH);  //Calculamos la distancia que registro a partir de las lecturas 
  distancia = duracion * 0.0343 / 2;
  
  if(distancia <= 15) {   //Configuramos la alerta del indicador de cercanía con un alcance de 15cm
    alertaDU = true; 
  }else {
    alertaDU = false;
  }

  // Distancia con sensor Sharp 
  valor = analogRead(A0); 
  distanciaSharp = 0.002 * pow(valor,2) - 0.7143 * valor + 73.059;   //Calculamos el valor registrado por el sensor Sharp de LDR

  if(distanciaSharp <= 15) {   //Configuramos la alerta del lector Sharp para indicar si hay obstaculo a 15 cm
    alertaDS = true; 
  }else {
    alertaDS = false;
  }
  imprimirInfo();   //Llamamos a la funciuon que depliega la informacion de los sensores en el monitor serial
  auxi = "                ";
  alertas();   //Llamamos a la funcion que indicara las alertas en el lcd
  delay(50);
}

// A imprimir 
// V: XX bits -- L: XX bits -- T: XX °C -- DU: XX cm -- DS: XX cm

void imprimirInfo() {
  lcd.setCursor(0,0);   //Imprimimos la luminosidad en el primer renglon del lcd
  lcd.print("L: ");
  lcd.print(valueLum);   //Imprimimos en el monitor serial los valores obtenidos de cada sensor
  lcd.print(" bits");
  Serial.print("V: ");
  Serial.print(voltaje);
  Serial.print(" bits -- ");
  Serial.print("L: ");
  Serial.print(valueLum);
  Serial.print(" bits -- ");
  Serial.print("T: ");
  Serial.print(tempC);
  Serial.print(" ºC -- ");
  Serial.print("DU: ");
  Serial.print(distancia);
  Serial.print(" cm -- ");
  Serial.print("DS: ");
  Serial.print(distanciaSharp);
  Serial.println(" cm -- ");
}

void alertas(){
  if(alertaVoltaje == true || alertaTemp == true || alertaDU == true || alertaDS == true ){  //Hacemos que prenda el led en caso de que haya alguna alerta activa sino se mantiene apagado
    digitalWrite(led, HIGH);
  }else{
    digitalWrite(led , LOW);
  }
    
  lcd.setCursor(0,1);

  //Configuramos los distintos casos de alertas que se pueden imprimir en el LCD y se lo asignamos a una variable auxiliar "auxi" que imprimir en el lcd despues de checar todas las alertas
  if(alertaVoltaje == false && alertaTemp == false && alertaDU ==false && alertaDS == true) {
    auxi = "S_Obstacle      ";
  }
  if(alertaVoltaje == false && alertaTemp == false && alertaDU ==true && alertaDS == false) {
    auxi = "U_Obstacle      ";
  }
  if(alertaVoltaje == false && alertaTemp == false && alertaDU ==true && alertaDS == true) {
    auxi = "UObs-SObs       ";
  }
  if(alertaVoltaje == false && alertaTemp == true && alertaDU ==false && alertaDS == false) {
    auxi = "Overheating     ";
  }
  if(alertaVoltaje == false && alertaTemp == true && alertaDU ==false && alertaDS == true) {
    auxi = "Temp-SObs       ";
  }
  if(alertaVoltaje == false && alertaTemp == true && alertaDU ==true && alertaDS == false) {
    auxi = "Temp-UObs       ";
  }
  if(alertaVoltaje == false && alertaTemp == true && alertaDU ==true && alertaDS == true) {
    auxi = "Temp-UObs-SObs  ";
  }
  if(alertaVoltaje == true && alertaTemp == false && alertaDU ==false && alertaDS == false) {
    auxi = "Low Battery     ";
  }
  if(alertaVoltaje == true && alertaTemp == false && alertaDU ==false && alertaDS == true) {
    auxi = "Bt-SObs         ";
  }
  if(alertaVoltaje == true && alertaTemp == false && alertaDU ==true && alertaDS == false) {
    auxi = "Bt-UObs         ";
  }
  if(alertaVoltaje == true && alertaTemp == false && alertaDU ==true && alertaDS == true) {
    auxi = "Bt-UObs-SObs    ";
  }
  if(alertaVoltaje == true && alertaTemp == true && alertaDU ==false && alertaDS == false) {
    auxi = "Bt-Temp         ";
  }
  if(alertaVoltaje == true && alertaTemp == true && alertaDU ==false && alertaDS == true) {
    auxi = "Bt-Temp-SObs    ";
  }
  if(alertaVoltaje == true && alertaTemp == true && alertaDU ==true && alertaDS == false) {
    auxi = "Bt-Temp-UObs    ";
  }
  if(alertaVoltaje == true && alertaTemp == true && alertaDU ==true && alertaDS == true) {
    auxi = "Bt-Temp-UObs-SOb";
  }
  

  lcd.print(auxi); //Imprimimos en el lcd las alertas correspondientes en el segundo renglon
}
