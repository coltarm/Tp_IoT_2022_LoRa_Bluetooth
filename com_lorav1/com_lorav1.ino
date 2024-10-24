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

char ssid[]= "ReseauLilian";
char pass[]= "cortux2003";
IPAddress ip;

WiFiClient espClient;
MqttClient mqttClient(espClient);


void setup() {
  Serial.begin(115200);

  pintMode(DI0, INPUT);
  SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(SS,RST,DI0);
  if(!LoRa.begin(freq)) {
    Serial.println("Starting LoRa failed !");
    while(1);
  }
  LoRa.setSpreadingFactor(sf);
  LoRa.setSignalBandwidth(sb);

  attachInterrupt(PIR, pinChanged, RISING);

  /*

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
  */
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

  Serial.println("New Packet");
  LoRa.beginPacket();
  sdp.data[0]=d1;
  sdp.data[1]=d2;
  LoRa.write(sdp.frame, 16);
  LoRa.endPacket();
  d1++;
  d2+=2;
  delay(2000);













  mqttClient.poll();

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
  /*
  reconnect();
  client.loop(); 
  float temp = random(30);
  mqtt_publish("tp_popo/Tamanoir",temp);
  Serial.print("qqchose : ");
  Serial.println(temp); delay(10000);
  */

}
