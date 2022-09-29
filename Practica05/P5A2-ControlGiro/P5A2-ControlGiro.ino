#define pot A0
#define mota 11
#define motb 10
float value = 0;
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
  Serial.print("Valor: ");
  Serial.println(voltaje);
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
  digitalWrite(mota, HIGH);
  digitalWrite(motb, LOW);
  Serial.println("Levogiro");
}
void dextrogiro(){
  digitalWrite(mota, LOW);
  digitalWrite(motb, HIGH);
  Serial.println("Dextrogiro");
}
void detenido(){
  digitalWrite(mota,LOW);
  digitalWrite(motb, LOW);
  Serial.println("Detenido");
}
