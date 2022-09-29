#define pot A0
#define mota 11
#define motb 10
#define pwm 9
float value = 0;
int pwmA = 0;

float voltaje;

void setup() {
  // put your setup code here, to run once:
  pinMode(mota, OUTPUT);
  pinMode(motb, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(pot);
  voltaje = (value/1023*5);
  pwmA = (value/4);
  potencia = map(pwmA, 0, 127, 1, 10);
  potencia2= map(pwmA, 127, 255, -1, -10);
  if(voltaje < 2){
    levogiro();
  }
  else if(voltaje <3){
    detenido();
  }
  else{
    dextrogiro();
  }
  
  
}

void  levogiro(){
  analogWrite(pwm, pwmA);
  digitalWrite(mota, HIGH);
  digitalWrite(motb, LOW);
  Serial.print("Sentido: Levogiro  ");
  Serial.print("Potenciometro: ");
  Serial.print(value);
  Serial.print("Motor: ");
  Serial.println(potencia);
}
void dextrogiro(){
  analogWrite(pwm, pwmA);
  digitalWrite(mota, LOW);
  digitalWrite(motb, HIGH);
  Serial.println("Sentido: Dextrogiro ");
  Serial.print("Potenciometro: ");
  Serial.print(value);
  Serial.print("Motor: ");
  Serial.println(potencia2);
}
void detenido(){
  analogWrite(pwm, pwmA);
  digitalWrite(mota,LOW);
  digitalWrite(motb, LOW);
  Serial.println("Sentido: Detenido ");
  Serial.print("Potenciometro: ");
  Serial.print(value);
  Serial.print("Motor: ");
  Serial.println("0 rpm");
}
