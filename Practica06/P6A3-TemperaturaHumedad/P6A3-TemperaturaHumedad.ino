# include "DHT.h"
 
# define DHTPIN 18      //Incluimos la libreria para usar DHT
# define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);    //Le asignamos el dht al pin que escogimos
String dato = "";

void setup() {
// put your setup code here, to run once:
Serial.begin(9600);
while(!Serial) {     //Esperamos a que haya comunicacion del monitor serial para iniciar el dht
;
}
dht.begin();

Serial.println("Dime que quieres");   //Preguntamos al usuario que valor desea consultar
Serial.println();
}

void loop() {

float humedad = dht.readHumidity();    //Leemos el valor de humedad del sensor
 
float tempC = dht.readTemperature();   //LEemos el valor de grados centigrados del sensor

float tempF = dht.readTemperature(true);  //Leemos el valor de grados fahrenheite del sensor


if (isnan(humedad) || isnan(tempC) || isnan(tempF)) {   //Preguntamos si el dht esta haciendo alguna lector para si no avisar
Serial.println(F("Failed to read from DHT sensor!"));
return;
}
if (Serial.available() > 0) {  //Si ya hay un valor ingresado en el monitor serial lo leemos 
dato = Serial.readString();
Serial.print(dato);


if (dato.equals("snsr tempC\n")) {  //Si el valor pide la temperatrura en centigrados la imprimimos
Serial.print("% TempC: ");
Serial.print(tempC);
Serial.println("°C ");
} 
if (dato.equals("snsr tempF\n")) {   //Si el valor del usuario pide la temperatura en Farenheit la imprimimos
Serial.print("° TempF: "); 
Serial.print(tempF);
Serial.println("°F ");
}   
if (dato.equals("snsr hum\n")) {    //Si el valor del usuario pide la humedad del sistema la imprimimos
Serial.print("Humedad: ");
Serial.print(humedad);
Serial.print("%");
}
}


}
