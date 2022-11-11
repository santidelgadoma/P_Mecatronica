# define motA1 4 // Pin de control del motor A
# define motA2 3 // Pin de control del motor A
# define motB1 6 // Pin de control del motor b
# define motB2 5 // Pin de control del motor b
# define enable1 2 // Enable motor 1 
# define enable2 7 // Enable motor 2


void setup() {
// put your setup code here, to run once:
// Definimos la comunicaciòn serial e inicializamos todos nuestros puertos como salidas 
Serial.begin(9600);
pinMode(motA1, OUTPUT);
pinMode(motA2, OUTPUT);
pinMode(motB1, OUTPUT);
pinMode(motB2, OUTPUT);
pinMode(enable1, OUTPUT);
pinMode(enable2, OUTPUT);
}

void loop() {
  // Hacemos uso de la funciòn DriveRobor en repetidas ocasiones 
  driveRobot(1,1); // Movimiento hacia delante
  delay(2000);
  driveRobot(-1,-1); // Movimiento hacia atràs 
  delay(2000);
  driveRobot(1,-1); // Movimiento a la izquierda
  delay(2000);
  driveRobot(-1,1); // Movimiento a la derecha 
  delay(2000);
  driveRobot(0,0); // Se queda quieto
  delay(2000);

}

// Mètodo que genera los movimientos por rueda
void driveRobot(float LSignal,float RSignal) {

// Si la señal de la rueda izquierda es menor a 0, entonces esta gira hacia atràs.
if(LSignal < 0) {
digitalWrite(motA1,HIGH);
digitalWrite(motA2,LOW);
digitalWrite(enable1, 10);
}

// Si la señal de la rueda izquierda es mayor a cero, entonces girarà hacia adelante.
if(LSignal > 0) {
digitalWrite(motA1,LOW);
digitalWrite(motA2,HIGH);
digitalWrite(enable1, 10);
}

// Si la señal es igual a 0, entonces se queda sin movimiento la rueda 
if(LSignal == 0) {
digitalWrite(motA1,LOW);
digitalWrite(motA2,LOW);
digitalWrite(enable1, 0);
}

// Si la señal de la rueda derecha es menor a cero, entonces girarà hacia atràs.
if(RSignal < 0) {
digitalWrite(motB1,LOW);
digitalWrite(motB2, HIGH);
digitalWrite(enable2, 10);
}

// Si la señal de la rueda derecha es mayor a cero, entonces girarà hacia adelante.
if( RSignal > 0) {
digitalWrite(motB1,HIGH);
digitalWrite(motB2,LOW);
digitalWrite(enable2, 10);
}

// Si la señal de la rueda derecha es igual a cero, entonces no se moverà esta rueda. 
if(RSignal == 0) {
digitalWrite(motB1,LOW);
digitalWrite(motB2,LOW);
digitalWrite(enable2, 0);
}


}
