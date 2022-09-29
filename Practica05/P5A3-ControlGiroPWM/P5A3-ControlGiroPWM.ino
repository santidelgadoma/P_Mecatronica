#define pot A0
#define mota 11
#define motb 10
#define pwm 9
float value = 0;
int pwmA = 0;
int potencia;
int potencia2;
int potenciaAux;
int potenciaAux2;

float voltaje;

void setup() {
  // put your setup code here, to run once:
  pinMode(mota, OUTPUT);
  pinMode(motb, OUTPUT);
  pinMode(pwm, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(pot);
  voltaje = (value/1023*5);
  pwmA = (value/4);
  potencia = map(pwmA, 0, 127, 1, 10);
  potencia2= map(pwmA, 127, 255, -1, -10);
  potenciaAux2 = map(pwmA, 127, 255, 10, 255);
  potenciaAux = map(pwmA, 0, 127, 255, 10);
  if(voltaje < 2){
    digitalWrite(mota, HIGH);
    digitalWrite(motb, LOW);
    analogWrite(pwm, potenciaAux); 
    Serial.print("Sentido: Levogiro  ");
    Serial.print("Potenciometro: ");
    Serial.print(pwmA);
    Serial.print(" Motor: ");
    Serial.println(potenciaAux);
  }
  else if(voltaje <3){
    digitalWrite(mota,LOW);
    digitalWrite(motb, LOW);
    analogWrite(pwm, pwmA);
    Serial.print("Sentido: Detenido ");
    Serial.print("Potenciometro: ");
    Serial.print(pwmA);
    Serial.print("Motor: ");
    Serial.println("0 rpm");
  }
  else{
    digitalWrite(mota, LOW);
    digitalWrite(motb, HIGH);
    analogWrite(pwm, potenciaAux2);
    Serial.print("Sentido: Dextrogiro ");
    Serial.print("Potenciometro: ");
    Serial.print(pwmA);
    Serial.print(" Motor: ");
    Serial.println(potenciaAux2);
  }
  
  
}
