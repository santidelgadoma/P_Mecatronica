
#define pot A2      //definimos los puertos por los que recibiremos los datos de las coordenadas X, Y, Z
#define pot2 A1
#define pot3 A0
float valueX;     // Declaramos una variable por cada coordinada para recibir el dato
float valueY;
float valueZ;

float xg,yg,zg;      //Declaramos una variable por cada coordinada para guardar el resultado de operaciones
float z_min = 262.0;  //Iniciamos las variables que obtuvimos como maximos y minimos de cada coordinada
float z_max = 400.5; 
float y_min = 257.0;
float y_max = 400.0;
float x_min = 256.0;
float x_max = 400.0;
float roll, pitch;   //Declaramos las variables roll y pitch para guardar los resultados


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  

}

void loop() {
  // put your main code here, to run repeatedly:
    valueX = analogRead(pot);  //Leemos el valor de x y lo guardamos

    valueY = analogRead(pot2);  //Leemos el valor de y y lo guardamos

    valueZ = analogRead(pot3);  //Leemos el valor de z y lo guardamos

    zg = map(valueZ, z_min, z_max, -100, 100);  //Mapeamos los valores entre 100 y -100
    zg = -zg/100;                               //Dividimos entre 100 para normalizar

    yg = map(valueY, y_min, y_max, -100, 100);
    yg = -yg/100;

    xg = map(valueX, x_min, x_max, -100, 100);
    xg = xg/100;

    pitch = xg/(sqrt(sq(yg) + sq(zg)));   //Calculamos el pitch con los datos obtenidos
    roll = yg/(sqrt(sq(xg) + sq(xg)));    //Calculamos el roll con los datos obtenidos

    pitch = (pitch*180)/3.1415;   //Lo cambiamos de radianes a grados
    roll = (roll*180)/3.1415;

    Serial.print("Xg: ");    //Imprimimos los valores para su comprobación
    Serial.print(xg );
    Serial.print(" Yg: ");
    Serial.print(yg );
    //Serial.print(" Zg: ");
    //Serial.print(zg );
    Serial.print(" Roll: ");
    Serial.print(roll);
    Serial.print(" Pitch: ");
    Serial.println(pitch);

    delay(150);
    
}
