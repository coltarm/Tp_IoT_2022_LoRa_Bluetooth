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
Pour envoyer des message à partir de LoRan, on défini les paramètre de transfert(fréquence, spread factor, la bande passante). On définit également le pin sur lequel on va émettre.
Au moment de l'envoie des paquets LoRa on défini la taille des paquets envoyé.

Groupe 2. Envoyer un message LoRa contenant une valeur venant d'un capteur.
Pour la réception de paquets utilisant la modulation LoRa, nous définissons les mêmes paramètres que pour l'envoi, tels que la fréquence, le débit binaire, et le mode LoRa. Cependant, nous ajoutons une fonction spécifique qui détermine le comportement du système en cas de réception d'un paquet. Cette fonction permet de traiter les données reçues, par exemple en les affichant, en les stockant, ou en déclenchant une action spécifique en fonction du contenu du paquet.

## 3. Inversion

Après avoir réussi une communication, la carte du groupe 1 et celle du groupe 2 inversent leurs rôles.


Colin TRÈVE
Florian NAVARRO
