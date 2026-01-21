#include <TheThingsNetwork.h>
#include <TheThingsMessage.h>
#include <SoftwareSerial.h>

// Set AppEUI and AppKey
const char *appEui = "9314122f9f48664f";
const char *appKey = "77F85835964FC8C511F87CE864B96A6D";

#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"
#define I2C_ADDRESS 0x3C
SSD1306AsciiAvrI2c oled;

SoftwareSerial loraSerial(10, 11); //TX, RX

#define debugSerial Serial
#define freqPlan TTN_FP_EU868

#define GAZ_SENSOR_PIN A0
#define LED_PIN 4

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

void setup()
{
  loraSerial.begin(57600);
  debugSerial.begin(57600);

  // Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000)
    ;

  debugSerial.println("-- STATUS");
  ttn.showStatus();

  debugSerial.println("-- JOIN");
  ttn.join(appEui, appKey);

  pinMode(LED_PIN, OUTPUT);

  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.setFont(Adafruit5x7);  
  oled.clear();
  oled.set2X();
  oled.println("Hello user1");

}

void loop()
{
  debugSerial.println("-- LOOP");

  byte GAZ_VALUE = analogRead(GAZ_SENSOR_PIN);
  debugSerial.print("GAZ_VALUE : ");
  debugSerial.println(GAZ_VALUE);
  if (GAZ_VALUE >100){
    digitalWrite(LED_PIN,HIGH);
    oled.clearField(0,2,5);
    oled.println("HELP");
  }else {
    digitalWrite(LED_PIN,LOW);
    oled.clearField(0,2,5);
  }

  ttn.sendBytes(&GAZ_VALUE, 1);

  delay(10000);
}