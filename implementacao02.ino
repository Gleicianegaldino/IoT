#include "DHT.h"

//import das bibliotecas
#include <WiFiEspClient.h>
#include <WiFiEsp.h>
#include <WiFiEspUdp.h>

#include "SoftwareSerial.h"

//Rx pino2 tx pino 3
SoftwareSerial esp8266(2,3);

#define DHTPIN 4
#define DHTTYPE DHT11

#define DEBUG true

//initialize
WiFiEspClient espclient;

//Configurações do wifi(ssid e senha)
#define WIFI_AP "esp"
#define WIFI_PASSWORD "12345678"

int status = WL_IDLE_STATUS;
unsigned long lastSend;

//Declarar o sensor
DHT dht (DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
      
  //inicializa
  dht.begin();

  //inicializa
  initWifi();

}

void loop() {
  // put your main code here, to run repeatedly:
  
  status = WiFi.status();
  if( status != WL_CONNECTED) {
    while( status != WL_CONNECTED) {
      Serial.print("Conectando à rede: ");
      Serial.println(WIFI_AP);
      //Connect
      status = WiFi.begin(WIFI_AP, WIFI_PASSWORD);
      delay(500);
  }
  Serial.println("Conectado");
}

  //metodo
  Aula1();

}

void Aula1() {
  Serial.println("Coletando dados");

  //lrndo a umidade
  float h =  dht.readHumidity();
  // "" temperatura
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Falha");
    return;
  }

  //impressao
  Serial.print("Unidade: ");
  Serial.print(h);
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C ");

  String temperature = String(t);
  String humidity = String(h);

  //impressao confirm
  Serial.print("Temperatura e Unidade: [");
  Serial.print(temperature); Serial.print(";");
  Serial.print(humidity);
  Serial.print("] ->");

  delay(5000);
}

//função para ser colocada no setup(conexão do módulo esp8266)
void initWifi() {
  
  //inicializa
  esp8266.begin(19200);
  
  WiFi.init(&esp8266);
  if (WiFi.status() == WL_NO_SHIELD) {
   Serial.println("WiFi shield not present");
   while (true);
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
