#include <LoRa.h>
#include <SPI.h>


#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DI0 26
#define freq 868E5
#define sf 8
#define sb 125E3


void onReceive (int packetSize);


void setup() {
 Serial.begin(9600);
 pinMode (DI0, INPUT); // pour activer le pin d'interruption
 // signal interrupt
 SPI.begin (SCK, MISO, MOSI, SS);
 LoRa.setPins (SS, RST, DI0);
 if (!LoRa.begin (freq)) {
   Serial.println("Starting LoRa failed!");
   while (1);
 }
 LoRa.setSpreadingFactor (sf);
 LoRa.setSignalBandwidth (sb);


 LoRa.onReceive(onReceive); // pour indiquer la fonction ISR
 LoRa.receive(); // pour activer 'interruption (une fois)
 Serial.println("test7777");
}


void onReceive (int packetSize)
{
 Serial.println("azerty");
 int i=0, rssi=0;
 char rdbuff [24], rbbuff [8];
 if (packetSize==24)
 {
   while (LoRa.available())
   {
     Serial.println("test55"); 
     rdbuff[i]=LoRa.read(); i++;
   }
   rssi=LoRa.packetRssi();
   // affichage des données reçues
   Serial.println("test1");
   Serial.println(rdbuff);
 }
 else{
   Serial.println("Packet size !=24");
 }
}


void loop()
{
 Serial.println("in the loop");
 delay (5000);
}



