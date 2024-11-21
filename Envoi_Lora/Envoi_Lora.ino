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

union pack
{
  uint8_t frame[16];
  float data[4];
} sdp;

void setup() {
 Serial.begin(115200);
 Serial.println("test");


 pinMode(DI0, INPUT);
 SPI.begin(SCK,MISO,MOSI,SS);
 LoRa.setPins(SS,RST,DI0);
 if(!LoRa.begin(freq)) {
   Serial.println("Starting LoRa failed !");
   while(1);
 }
 LoRa.setSpreadingFactor(sf);
 LoRa.setSignalBandwidth(sb);

  // put your setup code here, to run once:


}

float d1= 12.0, d2 = 321.54;
void loop() {
  Serial.println("nouveau paquet");
  LoRa.beginPacket();
  sdp.data[0]=d1;
  sdp.data[1] = d2;
  LoRa.write(sdp.frame, 16);
  LoRa.endPacket();
  d1++;
  d2+=2;
  delay(2000);
  // put your main code here, to run repeatedly:

}
