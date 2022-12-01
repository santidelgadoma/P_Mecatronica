# define LED 13

int estado;
int light_dif = 25;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  switch(estado){
    case 0:
      Serial.println("Estado 0");
      estado = 1;
      break;
      
     case 1:
      Serial.println("Estado 1");
      digitalWrite(LED, LOW);
      if (abs(light_dif) < 30){
        estado = 2;
      }
      else{
        estado = 0;
      }
      break;
    case 2:
      Serial.println("Estado 2");
      digitalWrite(LED, HIGH);
      delay(1000);
      estado = 0;
      break;
    
  
  }
}
