#include <LiquidCrystal_I2C.h>      //Incluimos la libreria para comunicarnos por I2C con el LCD



LiquidCrystal_I2C lcd(0x27,16,2);
# define motA1 4 // Pin de control del motor A
# define motA2 3 // Pin de control del motor A
# define motB1 6 // Pin de control del motor b
# define motB2 5 // Pin de control del motor b
# define enable1 2 // Enable motor 1 
# define enable2 7 // Enable motor 2
# define voltaje A0 // medidor de voltaje
# define fotoD A1  // primer fotoresistor
# define fotoI A2 // segundo fotoresistor
# define fotoA A3 // tercer fotoresistor
# define fotoRC A4  // cuarto fotoresistor
# define trig 53     // pin de trigger
# define echo 51    // pin de echo
# define sharpP A8 // primer sensor sharp
# define sharpS A9  // segundo sensor sharp

float voltajeI, voltajeA, voltajeRC, voltajeD, vsharpP, vsharpS, voltajeSistema, diferencia_luz,US_Sensor;  //definimos las variables que guardaran lo obtenido por los pines
int battery;

void setup() {
// put your setup code here, to run once:
// Definimos la comunicaciòn serial e inicializamos todos nuestros puertos como salidas para el motor y el de echo del ultrasonico como entrada. La pantalla lcd igual se inicia
  Serial.begin(9600);
  pinMode(motA1, OUTPUT);
  pinMode(motA2, OUTPUT);
  pinMode(motB1, OUTPUT);
  pinMode(motB2, OUTPUT);
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  lcd.init();
}

void loop() {
  // Hacemos uso de las funciones definidas que sensan el medio y imprimen los datos
       
 voltageSensor();
 distanceSensor();
 followLight();
 lcd_print();
 driveRobot(1,1);   //Movemos el robot 1 segundo hacia adelante y lo paramos
 delay(1000);
 driveRobot(0,0);
 delay(1000);
      
  }
  

// Mètodo que genera los movimientos por rueda dependiendo de las variables de entrada, mandando señales digitales al puente h
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
void voltageSensor(){
  voltajeSistema = analogRead(voltaje);  //leemos el voltaje de alimentación y si es menor a 650 bits ponemos battery = 0 para alertar de bajo voltage
  if(voltajeSistema > 650){
    battery = 1;
  }
  else{
    battery = 0;
  }
  
}
void lightSensor(){
  voltajeD = analogRead(fotoD);  //Sensamos la luz del medio con cuatro fotoresistores y usamos las de los lados para calcular la diferencia
  voltajeI = analogRead(fotoI);
  voltajeA = analogRead(fotoA);
  diferencia_luz = voltajeD - voltajeI;
  lcd.setCursor(0,0);
  lcd.print("L: ");
  lcd.print(voltajeI);
  lcd.setCursor(12,0);
  lcd.print("D: ");        // En el lcd imprimimos los datos para tener una interfaz del estado del robot
  lcd.print(voltajeD);
  lcd.setCursor(0,1);
  lcd.print("D: ");
  lcd.print(diferencia_luz);
  lcd.setCursor(8,1);
  lcd.print("A: ");
  lcd.print(voltajeA);


}
bool distanceSensor(){
  vsharpP = analogRead(sharpP);
  vsharpS = analogRead(sharpS);   //Sensamos los objetos que estan proximos a la locomocion con tres sensores (Dos Sharp y uno US)

  vsharpP = 1990*(pow(vsharpP, -0.921));  //Funcion de lectura del sharp
  vsharpS = 1990*(pow(vsharpS, -0.921));  
    // Distancia con  ultrasònico
  digitalWrite(trig, LOW);     //Hacemos el envío y recepción del pulso ultrasonico
  delayMicroseconds(2);
  
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  US_Sensor = pulseIn(echo, HIGH);  //Calculamos la distancia que registro a partir de las lecturas 
  US_Sensor = US_Sensor * 0.0343 / 2;
  if(US_Sensor < 8){
    obs = true;
  }
  else{
    obs = false;
  }

}

void followlight(){  //En esta función seguiremos la luz haciendo llamar la función driverobot
  
  if(diferencia_luz < -300){
    driveRobot(1,-1);  // corregimos por unos segundos hacia la derecha 
    delay(500);
    driveRobot(1,1);
  }
  else if(diferencia_luz > 300){
    driveRobot(-1,1); //Corregimos unos milisegundos a la derecha
    delay(200);
    driveRobot(1,1);

  }
  else{
    driveRobot(1,1); //estara en el umbral de luz para indicar que esta delante 
  }
  

  
}
void lcd_print(){
  lcd.setCursor(0,0);   //Imprimimos la diferencia de luz entre el lado derecho y izquierdo y tambien imprimimos el valor de battery
  lcd.print("light_dif: ");
  lcd.print(diferencia_luz);
  lcd.setCursor(0,1);
  lcd.print("battery: ");
  lcd.print(battery);
}
