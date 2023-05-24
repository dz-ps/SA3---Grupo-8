#include <DHTesp.h>
#include "WiFi.h"
#include "HTTPClient.h"
#include "PubSubClient.h"

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* topic = "johann";

#define LEDPIN1 12
#define LEDPIN2 14


#define DHT_PIN 15 // Definindo pino de dados do sensor
float temperatura=0;
float umidade=0;

DHTesp dhtSensor; // Definindo o objeto do sensor

WiFiClient espClient;

PubSubClient mqttClient(espClient);

void setup() {

  //sensor
  Serial.begin(115200);
  pinMode(LEDPIN1, OUTPUT);
  pinMode(LEDPIN2, OUTPUT);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  //wifi
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conectado...");
  
  //mqtt
  Serial.println("Conectando ao Broker Mqtt");
  mqttClient.setServer("broker.emqx.io", 1883);

  String clientId = "esp32Des_senai-" + String(random(0xffff), HEX);
  boolean isConected = mqttClient.connect(clientId.c_str());
  Serial.println(isConected);

  while(!mqttClient.connected()){
    String clientId = "osvaldo-";
    clientId += String(random(0xffff), HEX);
    if(mqttClient.connect(clientId.c_str())){
      Serial.println("Conectado ao Broker");
      mqttClient.subscribe(topic);
    } else {
      delay(500);
      Serial.println("Conectando ao broker...");
    }
  }
}

void loop() {
  
  //wifi
  HTTPClient http;

  String url = "https://api.thingspeak.com/update?api_key=PV1I1R52BY2A9S8R&field1=";

  TempAndHumidity data= dhtSensor.getTempAndHumidity();

  temperatura = data.temperature;
  umidade = data.humidity;

  url = url + temperatura + "&field2="+ umidade;

  //led
  if (temperatura>=35){ 
    digitalWrite(LEDPIN1, HIGH); 
  } else {
    digitalWrite(LEDPIN1, LOW);
  }

  if (umidade>=70){ 
    digitalWrite(LEDPIN2, HIGH); 
  } else {
    digitalWrite(LEDPIN2, LOW);
  }

  printf("Temperatura: %.1f°C   Humidade: %.1f%% \n", temperatura, umidade);  
  printf("+++++++++++++++++++++++++++++++++++++++\n");  

  //mqtt
  http.begin(url);
  int httpCode = http.GET();
  Serial.println(httpCode);
  if(httpCode >= 200 && httpCode <= 299){
    String payload = http.getString();
    Serial.println(payload);
  } else{
    Serial.println("Problemas ao conectar API.");
  }

  //mqttClient.publish(topic,"{\"temperatura\" :" temperatura ", \"humidade\" :" humidade\" }");
  String mqttPayload = "{\"temperatura\": " + String(temperatura) + ", \"umidade\": " + String(umidade) + "}";
  mqttClient.publish(topic, mqttPayload.c_str());

  delay;(1500); // espera por segundos
}
