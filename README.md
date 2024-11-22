# Tp_IoT_2022_LoRa_Bluetooth
Colin TRÈVE
Florian NAVARRO

Ce TP est à réaliser à deux groupes.

## 1. Mise en place

### 1. Installer l'IDE arduino et les dépendances nécessaires

cf. [http://www.smartcomputerlab.org/](http://www.smartcomputerlab.org/)

### 2. Se connecter sur un point d'accès Wifi
La connexion au Wifi sur les cartes fourni à été réalisé en utilisant le partage de connexion des téléphones portable.

### 3. Envoyer une message mqtt sur test.mosquitto.org tp_popo/alban
Le code se retrouve sur le fichier mqtt_msg.c

Pour envoyer un message en utilisant le protocole mqtt sur test.mosquitto.org, on a installer la librairie ArduinoMqqtClient.
Et on a instancié un client mqtt et précisé le broker sur lequel on voulait envoyé le message , dans notre cas test.mosquitto.org et le topic tp_popo/alban.
Et pour envoyer le message on précise que l'on commence un paquet, on indique le contenu et  la fin du paquet.

## 2. LoRa

### 1. Définir des valeurs communes (à faire au tableau)

### 2. Communiquer via mqtt des données
Le code se retrouve dans le répertoire mqtt_send_captions_value et mqtt_receive.

Groupe 1: Envoyer un message mqtt donnant les valeurs nécessaires à une reception via LoRa.
Pour envoyer un message mqtt en donnant les valeurs nécessaires pour une réception par LoRa. On définit les paramètre dans le message que l'on envoie comme précédément.
```c
sprintf(message, "{\"freq\": 8687E5, \"bandwidth\": 125, \"data\": \"Hello via LoRa %d\"}", counter);
```

Groupe 2. Ecouter les messages mqtt en en déduire les valeurs pour un envoi de données via Lora.


### 3. Communiquer via LoRa des données

Groupe 1: Écouter les messages LoRa et les afficher.

Groupe 2. Envoyer un message LoRa contenant une valeur venant d'un capteur.

## 3. Inversion

Après avoir réussi une communication, la carte du groupe 1 et celle du groupe 2 inversent leurs rôles.

## 4. Bluetooth (ou BLE)

À la place de communiquer les valeurs venant d'un capteur, continuer la discussion pour ouvrir un canal Bluetooth.

Colin TRÈVE
Florian NAVARRO
