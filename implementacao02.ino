#include "DHT.h"

//import das bibliotecas
#include <WifiEspClient.h>
#include <WifiEsp.h>
#define DHTPIN 4
#define DHTTYPE DHT11

#include "SoftwareSerial.h"
//Rx pino2 tx pino 3
SoftwareSerial esp8266(2,3);

#define DEBUG true


WifiEspClient espclient;
//Configurações do wifi(ssid e senha)
#define WIFI_AP "";
#define WIFI_PASSWORD "";


int status = WL_IDLE_STATUS;
unsigned long lastSend;

//Declarar o sensor
DHT dht (DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);

dht.begin();
initWifi();
}

void loop() {
  // put your main code here, to run repeatedly:

status=WiFi.status();
if(status !=WL_CONNECTED){
  while(status !=WL_CONNECTED){
    Serial.print("Conectando à rede: ")
    Serial.println(WIFI_AP);
     status=WiFi.begin(WIFI_AP,WIFI_PASSWORD);
     delay(500);
  }
  Serial.println("Conectado");
}

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

//função para ser colocada no setup(conexão do módulo esp8266)
void initWifi(){
  esp8266.begin(19200);
  WiFi.init(esp8266);
 if(WiFi.status()==WL_NO_SHIELD){
   Serial.println("");
   While (true);

 }

 Serial.println("Conectando à rede...");
 while (status !=WL_CONNECTED) {
   Serial.print("Esperando conexão com a rede:");
   Serial.println(WIFI_AP);
  //Conectado a rede WPA/WPA2
   status=WiFi.begin(WIFI_AP,WIFI_PASSWORD);
   delay(500);
 }
 Serial.println("Conectado à rede: ");
 Serial.println(WiFi.localIP());//impressão do IP da rede

}

