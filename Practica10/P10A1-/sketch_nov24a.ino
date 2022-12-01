#define motA1 4 // Pin de control del motor A
#define motA2 3 // Pin de control del motor A
#define motB1 6 // Pin de control del motor b
#define motB2 5 // Pin de control del motor b
#define enable1 2 // Enable motor 1
#define enable2 7 // Enable motor 2
#define voltaje A0 // medidor de voltaje
#define fotoD A1 // primer fotoresistor
#define fotoI A2 // segundo fotoresistor
#define fotoA A3 // tercer fotoresistor
#define fotoRC A4 // cuarto fotoresistor
#define trig 53 // pin de trigger
#define echo 51 // pin de echo
#define sharpP A8 // primer sensor sharp
#define sharpS A9 // segundo sensor sharp

float L_LDR, R_LDR, B_LDR, vsharpP, vsharpS, voltajeSistema, diferencia_luz; //definimos las variables que guardaran lo obtenido por los pines
float US_Sensor;
int battery;
float B_UMBRAL = 160;
float UMBRAL_SUPERIOR = 50; 
float UMBRAL_INFERIOR= -50;
void setup() {
// put your setup code here, to run once:
// Definimos la comunicaciòn serial e inicializamos todos nuestros puertos como salidas y el de echo del ultrasonico como entrada
Serial.begin(9600);
pinMode(motA1, OUTPUT);
pinMode(motA2, OUTPUT);
pinMode(motB1, OUTPUT);
pinMode(motB2, OUTPUT);
pinMode(enable1, OUTPUT);
pinMode(enable2, OUTPUT);
pinMode(trig, OUTPUT);
pinMode(echo, INPUT);
}

void loop() {
// Hacemos uso de las funciones definidas que sensan el medio y imprimen los datos
lightSensor();
followLight();
//voltageSensor();
//distanceSensor();
//temperatureSensor();
//lcd_print();
}

void followLight() {
  while(B_LDR >= B_UMBRAL) {
    driveRobot(1,-1);
    lightSensor();
  } 
  driveRobot(0,0); //frenamos el moviemiento del robot para poder dar lugar al siguiente moviemiento. 

  while(diferencia_luz > UMBRAL_INFERIOR && diferencia_luz < UMBRAL_SUPERIOR) {
    driveRobot(1,1); // Si la luz se encuentra al frente, entonces avanzamos hacia ella en dirección recta. 
    lightSensor(); 
  }
  driveRobot(0,0);

 while(diferencia_luz > UMBRAL_SUPERIOR) {
    driveRobot(-1,1); // Giramos el robot hacia la izquierda hasta que se posicione e dirección a la luz. 
    lightSensor();
  }
    driveRobot(0,0);

  while(diferencia_luz < UMBRAL_INFERIOR) {
    driveRobot(1,-1);
    lightSensor(); 
  }
  driveRobot(0,0);

}

// Mètodo que genera los movimientos por rueda
void driveRobot(float LSignal,float RSignal) {

  if(LSignal < 0 && RSignal < 0 ) { 
    digitalWrite(motB2,HIGH);
    digitalWrite(motB1,LOW);
    digitalWrite(enable2, 40);
    digitalWrite(motA2,HIGH);
    digitalWrite(motA1,LOW);
    digitalWrite(enable1, 85);
  }
  if(LSignal < 0 && RSignal == 0 ) { 
    digitalWrite(motB2,LOW);
    digitalWrite(motB1,LOW);
    digitalWrite(enable2, 0);
    digitalWrite(motA2,HIGH);
    digitalWrite(motA1,LOW);
    digitalWrite(enable1, 85);
  }
  if(LSignal < 0 && RSignal > 0 ) { 
    digitalWrite(motB2,LOW);
    digitalWrite(motB1,HIGH);
    digitalWrite(enable2, 40);
    digitalWrite(motA2,HIGH);
    digitalWrite(motA1,LOW);
    digitalWrite(enable1, 85);
  }
  if(LSignal == 0 && RSignal == 0 ) { 
    digitalWrite(motB2,LOW);
    digitalWrite(motB1,LOW);
    digitalWrite(enable2, 0);
    digitalWrite(motA2,LOW);
    digitalWrite(motA1,LOW);
    digitalWrite(enable1, 0);
  }
  if(LSignal == 0 && RSignal < 0) { 
    digitalWrite(motB2,HIGH);
    digitalWrite(motB1,LOW);
    digitalWrite(enable2, 40);
    digitalWrite(motA2,LOW);
    digitalWrite(motA1,LOW);
    digitalWrite(enable1, 0);
  }
  if(LSignal == 0 && RSignal > 0) { 
    digitalWrite(motB2,LOW);
    digitalWrite(motB1,HIGH);
    digitalWrite(enable2, 40);
    digitalWrite(motA2,LOW);
    digitalWrite(motA1,LOW);
    digitalWrite(enable1, 85);
  }
  if(LSignal > 0 && RSignal > 0) { 
    digitalWrite(motB2,LOW);
    digitalWrite(motB1,HIGH);
    digitalWrite(enable2, 40);
    digitalWrite(motA2,LOW);
    digitalWrite(motA1,HIGH);
    digitalWrite(enable1, 85);
  }
  if(LSignal > 0 && RSignal == 0) { 
    digitalWrite(motB2,LOW);
    digitalWrite(motB1,LOW);
    digitalWrite(enable2, 40);
    digitalWrite(motA2,LOW);
    digitalWrite(motA1,HIGH);
    digitalWrite(enable1, 85);
  }
  if(LSignal > 0 && RSignal < 0) { 
    digitalWrite(motB2,HIGH);
    digitalWrite(motB1,LOW);
    digitalWrite(enable2, 40);
    digitalWrite(motA2,LOW);
    digitalWrite(motA1,HIGH);
    digitalWrite(enable1, 85);
  }

}
void voltageSensor() {
voltajeSistema = analogRead(voltaje); //leemos el voltaje de alimentación y si es menor a 650 bits ponemos battery = 0
if (voltajeSistema > 650) {
battery = 1;
} else {
battery = 0;
}
}
void lightSensor() {
  R_LDR = analogRead(fotoD); //Sensamos la luz del medio con cuatro fotoresistores y usamos las de los lados para calcular la diferencia
  L_LDR = analogRead(fotoI) - 200; // Restamos 200 para hacer tender la diferencia a 0 en estado inicial. 
  B_LDR = analogRead(fotoA);
  diferencia_luz = R_LDR - L_LDR;
}
void distanceSensor() {
  vsharpP = analogRead(sharpP);
  vsharpS = analogRead(sharpS); //Sensamos los objetos que estan proximos a la locomocion con tres sensores (Dos Sharp y uno US)
  
  vsharpP = 1990 * (pow(vsharpP, -0.921)); //Funcion de lectura del sharp
  vsharpS = 1990 * (pow(vsharpS, -0.921));
  // Distancia con ultrasònico
  digitalWrite(trig, LOW); //Hacemos el envío y recepción del pulso ultrasonico
  delayMicroseconds(2);
  
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  US_Sensor = pulseIn(echo, HIGH); //Calculamos la distancia que registro a partir de las lecturas
  US_Sensor = US_Sensor * 0.0343 / 2;
}
