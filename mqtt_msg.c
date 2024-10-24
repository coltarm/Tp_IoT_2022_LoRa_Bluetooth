#include <ArduinoMqttClient.h>
//#include <ThingSpeak.h>
#include <WiFi.h>

//MQTT
#define broker       "test.mosquitto.org"
#define port  1883
#define MQTT_USERNAME     "Tamanoir"
const char topic[] = "tp_popo/Tamanoir";


char ssid[]= "RedmiF";
char pass[]= "x5pihawjk9a8rqn";
IPAddress ip;

WiFiClient espClient;
MqttClient mqttClient(espClient);

const long interval = 80000;
unsigned long previousMillis = 0;
int count = 0;

void setup() {
  Serial.begin(9600);
  WiFi.disconnect(true);
  delay(1000);
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  IPAddress ip = WiFi.localIP();
  Serial.print("IPAddress : ");
  Serial.println(ip);
  Serial.print("Wifi setup ok");
  delay(1000);
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
  //client.publish("tp_popo/Tamanoir", "Hello from Florian");
}

void loop() {
  mqttClient.poll();
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time a message was sent
    previousMillis = currentMillis;

    char msg[] = "Hello from Florian";

    Serial.print("Sending message to topic: ");
    Serial.println(topic);
    Serial.println(msg);

    mqttClient.beginMessage(topic);
    mqttClient.print(msg);
    mqttClient.endMessage();
  }
  /*
  reconnect();
  client.loop(); 
  float temp = random(30);
  mqtt_publish("tp_popo/Tamanoir",temp);
  Serial.print("qqchose : ");
  Serial.println(temp); delay(10000);
  */

}

