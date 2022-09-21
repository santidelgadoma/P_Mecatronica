//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1               

#include <LiquidCrystal_I2C.h> //Incluir la biblioteca para poder comunicarnos con el lcd usando I2C

int desplazo = 19;  //Declaramos la variable de desplaso

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.

  

}
void loop()
{
   lcd.backlight();
  lcd.setCursor(desplazo,0);   //El procedimiento es el mismo a el código pasado lo que cambia es la comunicacion entre la placa arduino y el lcd
  lcd.print("Santi D");
  lcd.print(" ");
  lcd.setCursor(desplazo + 3, 1);
  lcd.print("Juan H");
  lcd.print(" ");
  desplazo = desplazo - 1;
  delay(350);
  if(desplazo == 0){
    exit(0);
  }
}
