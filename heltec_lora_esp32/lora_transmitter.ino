
#include "heltec.h"
//Im using heltec board so I included those libraries
//I live in asia so the frequency alloted is 433mhz
#define BAND    433E6  //you can set band here directly,e.g. 868E6,915E6
//In this project I'm transfering the values of potentiometer through lora and this gave me a range of about 1km this can be increased by increasing the
//size of the antenna and also the height of the transmitter
String rssi = "RSSI --";
String packSize = "--";
String packet ;
void setup()
{
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();  
  Heltec.display->setFont(ArialMT_Plain_10);
  delay(1500);
  Heltec.display->clear();
  
  Heltec.display->drawString(0, 0, "Heltec.LoRa Initial success!");
  Heltec.display->display();
  delay(1000);
}
  
void loop()
{//on pin 36 I have kept a potentiometer and the reading are displayed on the screen and these values are sent through lora to the receiver 
  int x=analogRead(36);
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  
  Heltec.display->drawString(0, 0, Value of potentiometer is :");
  Heltec.display->drawString(90, 0, String(x));
  Heltec.display->display();

  // intialises the transmission of data through lora
  LoRa.beginPacket();
  
/*
 * LoRa.setTxPower(txPower,RFOUT_pin);
 * txPower -- 0 ~ 20
 * RFOUT_pin could be RF_PACONFIG_PASELECT_PABOOST or RF_PACONFIG_PASELECT_RFO
 *   - RF_PACONFIG_PASELECT_PABOOST -- LoRa single output via PABOOST, maximum output 20dBm
 *   - RF_PACONFIG_PASELECT_RFO     -- LoRa single output via RFO_HF / RFO_LF, maximum output 14dBm
*/
  LoRa.setTxPower(14,RF_PACONFIG_PASELECT_PABOOST);
  LoRa.print("Teja sent this:");
  LoRa.print(x);
  LoRa.endPacket();
                      // wait for a second
}