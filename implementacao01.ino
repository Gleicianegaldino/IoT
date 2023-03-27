#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11

//Declarar o sensor
DHT dht (DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);

dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

Aula1();

}

void Aula1(){
  Serial.println("Coletando dados");

  float h =  dht.readHumidity();

  float t = dht.readTemperature();

if (isnan(h) || isnan(t)){
  Serial.println("Falha");
  return;
}

Serial.print("Unidade: ");
Serial.print(h);
Serial.print("Temperatura: ");
Serial.print(t);
Serial.print(" *C ");

String temperature = String(t);
String humidity = String(h);

Serial.print("Temperatura e Unidade: [");
Serial.print(temperature); Serial.print(";");
Serial.print(humidity);
Serial.print("] ->");

delay(5000);
}

