#include <LiquidCrystal.h> //Incluimos las librerias que permitiran la comunicacion con el LCD

#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);  // Declaramos una instancia del lcd con los puertos a los que lo conectamos
int desplazo = 19;   //Declaramos una variable desplazo que permitira desplazar uno de los nombres

void setup() {
  lcd.begin(16,2);   // Iniciamos el LCD con 16 columnnas y 2 filas

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(desplazo,0);  // Nos colocamos sobre la primera fila y la columna de desplazo que aparece fuera del lcd
  lcd.print("Santi D");  // Donde nos colocamos ponemos el primer nombre
  lcd.print(" ");   //Borramos lo imprimido para poder mover el nombre por el lcd
  lcd.setCursor(desplazo + 3,1);  //Nos colocamos en la segunda fila y la columna de deplazo + 3 para que esten en escalera
  lcd.print("Juan H"); //Donde nos colocamos imprimimos el segundo nombre
  lcd.print(" ");   //Borramos lo imprimido para poder mover el nombre por el lcd
  desplazo = desplazo -1; //Decrementamos desplazo para que se vaya cambiando la posición de los nombres
  if(desplazo == 0){ //Si la variable desplazo llega al valor 0 detenemos el loop 
    exit(0);
  }
  delay(350);
  
}
