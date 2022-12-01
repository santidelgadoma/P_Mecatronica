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
      Serial.println("Estado 0");   //Comenzamos en el estado cero y de inmediato cambiamos al estado 1
      estado = 1;
      break;
      
     case 1:
      Serial.println("Estado 1");
      digitalWrite(LED, LOW);
      if (abs(light_dif) < 30){. //En el estado 1 segun la variable light_diff nos regresamos al estado 0 o avazamos al estado 2
        estado = 2;
      }
      else{
        estado = 0;
      }
      break;
    case 2:
      Serial.println("Estado 2"); //En el estado 2 activamos el led durante un segundo y regresamos al estado inicial
      digitalWrite(LED, HIGH);
      delay(1000);
      estado = 0;
      break;
    
  
  }
}
