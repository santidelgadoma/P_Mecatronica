#define mota 11
#define motb 10


void setup() {
  // put your setup code here, to run once:
  pinMode(mota, OUTPUT);
  pinMode(motb, OUTPUT);  
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(mota, HIGH);
  digitalWrite(motb, LOW);
  Serial.println("Levogiro");
  delay(2000);

  digitalWrite(mota, LOW); 
  digitalWrite(motb, LOW);
  Serial.println("Freno pasivo");
  delay(2000);  

  digitalWrite(mota, LOW);
  digitalWrite(motb, HIGH);
  Serial.println("Dextrogiro");
  delay(2000);

  digitalWrite(mota, HIGH);
  digitalWrite(motb, HIGH);
  Serial.println("Freno activo");
  delay(2000);

}
