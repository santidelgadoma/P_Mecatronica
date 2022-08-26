#define pot A0
#define led 13
float value = 0;
float voltaje;
void setup() {
  // No definimos pinMode porque directamennte leeremos una entrada analógica
  pinMode(led, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  value = analogRead(pot) ;
  voltaje = (value/1023*5);
  Serial.print("Voltaje: ");
  Serial.print(voltaje);
  Serial.println("V");
  delay(100);

  if (voltaje > 3) {
    digitalWrite(led, HIGH);
  }

  else{
    digitalWrite(led, LOW);
  }

}
