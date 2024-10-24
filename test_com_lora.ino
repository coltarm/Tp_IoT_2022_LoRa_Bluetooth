#include <WiFi.h>
#include <PubSubClient.h>

// Configuration réseau WiFi
const char* ssid = "ReseauLilian";
const char* password = "cortux2003";

// Configuration serveur MQTT
const char* mqtt_server = "test.mosquitto.org";
const char* mqtt_topic = "tp_popo/LoRaSetup";

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

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connexion au serveur MQTT...");
    if (client.connect("HeltecLoRa1")) {
      Serial.println("connecté");
      
      // Envoyer les paramètres LoRa via MQTT
      String message = "{\"freq\": 915, \"bandwidth\": 125, \"data\": \"Hello via LoRa\"}";
      client.publish(mqtt_topic, message.c_str());
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


