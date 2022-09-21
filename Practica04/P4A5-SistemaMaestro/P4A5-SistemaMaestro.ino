//Código para el maestro

# include <Wire.h>  //incluimos la libreria para transmitir
#include <LiquidCrystal_I2C.h> //incluimso la libreria para usar el I2C para comunicarse con el led
LiquidCrystal_I2C lcd(0x27,16,2); // Definimos los pines que usará el lcd

#define pot A2   //definimos el puerto para recibir los valores de X
#define pot2 A1  //definimos el puerto para recibir los valores de Y
#define pot3 A0  //definimos el puerto para recibir los valores de Z

float valueX;   // Instanciamos las variables en las que guardaremos los valores de x,y,x
float valueY;
float valueZ;

float xg,yg,zg;   //Instanciamos las variables donde guardaremos los valores estandarizados
float z_min = 262.0;  //Instanciamos los valores que recopilamos moviendo el acelerometro 
float z_max = 400.5;
float y_min = 257.0;
float y_max = 400.0;
float x_min = 256.0;
float x_max = 400.0;
float roll;  //Instanciamos la variable para calcular el roll del sistema
int angulo;   //Instanciamos la variable con la que mandaremos el valor del angulo al nodo esclavo

void setup() {  //Iniciamos la comunicación con los nodos esclavos y se incia el lcd 
Wire.begin();
Serial.begin(9600);
lcd.init(); 

}

void loop() {
valueX = analogRead(pot);  //leemos los valores de X 

valueY = analogRead(pot2); //leemos los valores de Y

valueZ = analogRead(pot3);  //leemos los valores de Z

zg = map(valueZ, z_min, z_max, -100, 100); //Estandarizamos los valores con respecto al maximo y minimo calculado
zg = -zg/100;                              //Normalizamos los valores 
yg = map(valueY, y_min, y_max, -100, 100);
yg = -yg/100;
xg = map(valueX, x_min, x_max, -100, 100);
xg = xg/100;
roll = yg/(sqrt(sq(xg) + sq(zg)));       // Calculamos el roll con la formula proporcionada

roll = (roll*180)/3.1415;               // Transformamos los valores de radianes a grados

if(roll == -90){                        // Implementamos las condiciones para cumplir con la tabla proporcionada
angulo = 0;
}
else {
if(roll == 0) {
angulo = 45;
}
else {
if(roll == 90) {
angulo = 90;
}
}
}
if(roll >= -89 and roll <=-1) {     //Mapeamos los valores recibidos para cumplir con la tabla proporcionada
angulo = map(roll,-89,-1,1,44);
}
if(roll >= 1 and roll <= 89) {
angulo = map(roll,1,89,45,89);
}
// LCD
lcd.backlight();              //Configuramos el lcd para imprimir el angulo del acelerometro y el dato que se manda al Servo
lcd.setCursor(4,0);
lcd.print("Angulo: ");
lcd.print(roll);
lcd.setCursor(4,1);
lcd.print("DatoIC2: ");
lcd.print(angulo);
delay(1000);
Wire.beginTransmission(0xAF);  //Configuramos la transmision con el valor AF
Wire.write(angulo);            //Mandamos el valor del angulo por el canal de transmision
Wire.endTransmission();        
}
