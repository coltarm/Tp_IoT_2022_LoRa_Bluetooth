#include <ArduinoMqttClient.h>
#include <WiFi.h>
#define PIR 17

bool MOTION_DETECTED = false;
void pinChanged() {
  MOTION_DETECTED = true;
}

int counter=0;

//MQTT
#define broker       "test.mosquitto.org"
#define port  1883
#define MQTT_USERNAME     "Tamanoir"

const char topic[] = "tp_popo/LoRaSetup";

char ssid[]= "Rnom_wifi";
char pass[]= "MDP";
IPAddress ip;

WiFiClient espClient;
MqttClient mqttClient(espClient);


void setup() {
  Serial.begin(115200);

  attachInterrupt(PIR, pinChanged, RISING);

  delay(1000);  
}


float d1=12.0, d2=321.54;

void loop() {

  int i = 0;
  if(MOTION_DETECTED) {
    Serial.println("MOTION DETECTED");
    delay(1000); counter++;
    MOTION_DETECTED = false;
    Serial.println(counter);
  }


  char msg[] = "Hello from Florian/Colin";
  char message[100];
  sprintf(message, "{\"freq\": 8687E5, \"bandwidth\": 125, \"data\": \"Hello via LoRa %d\"}", counter);
  //String message = "{\"freq\": 8687E5, \"bandwidth\": 125, \"data %s\": \counter "Hello via LoRa counter\"}";
  Serial.print("Sending message to topic: ");
  Serial.println(topic);
  Serial.println(message);

  mqttClient.beginMessage(topic);
  mqttClient.print(message);
  mqttClient.endMessage();
  delay(4000);
  

}
