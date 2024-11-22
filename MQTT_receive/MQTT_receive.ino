#include <WiFi.h>
#include <PubSubClient.h>
#include <LoRa.h>


// Configuration du réseau WiFi
const char* ssid = "nom_wifi";  // Remplacez par votre SSID WiFi
const char* password = "MDP";  // Remplacez par votre mot de passe WiFi


// Serveur MQTT
const char* mqtt_server = "test.mosquitto.org";
const char* mqtt_topic = "tp_popo/LoRaSetup";


// Variables pour LoRa
int loraFreq;
int loraBandwidth;
String loraData;


// Client WiFi et MQTT
WiFiClient espClient;
PubSubClient client(espClient);


void setup_wifi() {
 delay(10);
 WiFi.begin(ssid, password);


 while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
 }


 Serial.println("WiFi connecté");
}


// Fonction de rappel appelée lorsque des messages MQTT sont reçus
void callback(char* topic, byte* payload, unsigned int length) {
 String message;


 for (int i = 0; i < length; i++) {
   message += (char)payload[i];
 }


 // Extraction des paramètres (simples ici, ils peuvent être plus complexes)
 if (message.indexOf("freq") != -1) {
   loraFreq = message.substring(message.indexOf("freq") + 7, message.indexOf(",")).toInt();
   loraBandwidth = message.substring(message.indexOf("bandwidth") + 11, message.lastIndexOf(",")).toInt();
   loraData = message.substring(message.indexOf("data") + 7, message.indexOf("\"}"));
  
  
   LoRa.begin(loraFreq); 
   LoRa.setSignalBandwidth(loraBandwidth);  // Bande passante LoRa
  
   LoRa.beginPacket();
   LoRa.print(loraData);
   LoRa.endPacket();
  
   Serial.println("Données envoyées via LoRa : " + loraData);
 }
}


void setup() {
 Serial.begin(115200);
 setup_wifi();
 client.setServer(mqtt_server, 1883);
 client.setCallback(callback);


 // Initialiser LoRa avec broches personnalisées pour Heltec
 LoRa.setPins(18, 14, 26);  // NSS, RST, DIO0
 if (!LoRa.begin(8687E5)) {
   Serial.println("Erreur d'initialisation LoRa !");
   while (1);
 }
}


void reconnect() {
 while (!client.connected()) {
   Serial.print("Connexion au serveur MQTT...");
   if (client.connect("HeltecLoRa2")) {
     Serial.println("connecté");
     client.subscribe(mqtt_topic);
   } else {
     Serial.print("échec, rc=");
     Serial.print(client.state());
     delay(5000);
   }
 }
}


void loop() {
 if (!client.connected()) {
   reconnect();
 }
 client.loop();
}
