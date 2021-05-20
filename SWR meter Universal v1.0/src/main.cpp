/**
 * 
 * ESP32-based 2KW SWR/Power meter AD8310 based
 * 
 * Project description http://vk6nx.net/06_projects.html
 * Source code: http://github.com/VK6NX/PAcontrol
 * 
 * 
 */

#define MECH_DEBUG 1

#include <SPI.h>
#include <WiFiUdp.h>

#include "mainconfig.h"
#include "Syslog.h"
#include "mqttinit.h"
#include "ota.h"
#include "adc.h"
#include "tftdisplay.h"


WiFiUDP udpClient;

#define SYSLOG_SERVER  "192.168.1.251" // Change IP to reflect syslog server in your environment.
#define SYSLOG_PORT 514
#define DEVICE_HOSTNAME mqttNAME

Syslog syslog(udpClient, SYSLOG_SERVER, SYSLOG_PORT, DEVICE_HOSTNAME, LOG_KERN);


void setup() {
  Serial.begin(115200);
  wifiMqttInit();		// Comment if there is no WiFi requirement
  otaInit();			// Comment if there is no WiFi requirement
  adcInit();
  displayInit();

  syslog.log(LOG_WARNING, String(mqttNAME) + "after boot setup completed");
}

void displaySWRvalue() {                     // display SWR values
  if (valueSWR != 0){
    dtostrf(valueSWR, 2, 2, DisplayValueSWR);
    tft.setTextSize(2);
    tft.setCursor(55, 15);
    tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
    tft.print(DisplayValueSWR);
  }
  else{
    tft.setTextColor(ST77XX_BLACK, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.setCursor(55, 15);
    tft.print("000000");
    delay(1);
    tft.setTextColor(ST77XX_BLACK, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.setCursor(55, 15);
    tft.print("111111");
    delay(1);
    tft.setTextColor(ST77XX_BLACK, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.setCursor(55, 15);
    tft.print("222222");
    delay(1);
    tft.setTextColor(ST77XX_BLACK, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.setCursor(55, 15);
    tft.print("333333");
    delay(1);
    tft.setTextColor(ST77XX_BLACK, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.setCursor(55, 15);
    tft.print("444444");
    delay(1);
    tft.setTextColor(ST77XX_BLACK, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.setCursor(55, 15);
    tft.print("555555");
    delay(1);
    tft.setTextColor(ST77XX_BLACK, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.setCursor(55, 15);
    tft.print("666666");
    delay(1);
    tft.setTextColor(ST77XX_BLACK, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.setCursor(55, 15);
    tft.print("777777");
    delay(1);
    tft.setTextColor(ST77XX_BLACK, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.setCursor(55, 15);
    tft.print("888888");
    delay(1);
    tft.setTextColor(ST77XX_BLACK, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.setCursor(55, 15);
    tft.print("999999");
  }
}



void displayPvalue() {                      // display PWR values
  if (fwdPwrVal != 0){
    dtostrf(fwdPwrVal, 4, 0, DisplayValueP);
    tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
    tft.setCursor(55, 40);
    tft.setTextSize(2);                         // set the font x2
    tft.print(DisplayValueP);
  }
  else {
    tft.setTextColor(ST77XX_BLACK, ST77XX_BLACK);
    tft.setCursor(55, 40);
    tft.setTextSize(2);
    tft.print("0000");
    delay(1);
    tft.setCursor(55, 40);
    tft.setTextSize(2);
    tft.print("1111");
    delay(1);
    tft.setCursor(55, 40);
    tft.setTextSize(2);
    tft.print("2222");
    delay(1);
    tft.setCursor(55, 40);
    tft.setTextSize(2);
    tft.print("3333");
    delay(1);
    tft.setCursor(55, 40);
    tft.setTextSize(2);
    tft.print("4444");
    delay(1);
    tft.setCursor(55, 40);
    tft.setTextSize(2);
    tft.print("5555");
    delay(1);
    tft.setCursor(55, 40);
    tft.setTextSize(2);
    tft.print("6666");
    delay(1);
    tft.setCursor(55, 40);
    tft.setTextSize(2);
    tft.print("7777");
    delay(1);
    tft.setCursor(55, 40);
    tft.setTextSize(2);
    tft.print("8888");
    delay(1);
    tft.setCursor(55, 40);
    tft.setTextSize(2);
    tft.print("9999");
  }
}

void displayPvaluemW(){
  if (fwdPwrVal > 0 && fwdPwrVal < 1){
    dtostrf(fwdPwrVal, 0, 3, DisplayValuePmW);
    tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.setCursor(55, 60);
    tft.print(DisplayValuePmW);
  }
  else if (fwdPwrVal >= 1 && fwdPwrVal < 10){
    dtostrf(fwdPwrVal, 0, 2, DisplayValuePmW);
    tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.setCursor(55, 60);
    tft.print(DisplayValuePmW);
  }
  else if (fwdPwrVal >= 10 && fwdPwrVal < 100){
    dtostrf(fwdPwrVal, 0, 1, DisplayValuePmW);
    tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.setCursor(55, 60);
    tft.print(DisplayValuePmW);
  }
  else{
    tft.setTextColor(ST77XX_BLACK, ST77XX_BLACK);
    tft.setCursor(55, 60);
    tft.setTextSize(2);
    tft.print("000000");
    delay(1);
    tft.setCursor(55, 60);
    tft.setTextSize(2);
    tft.print("111111");
    delay(1);
    tft.setCursor(55, 60);
    tft.setTextSize(2);
    tft.print("222222");
    delay(1);
    tft.setCursor(55, 60);
    tft.setTextSize(2);
    tft.print("333333");
    delay(1);
    tft.setCursor(55, 60);
    tft.setTextSize(2);
    tft.print("444444");
    delay(1);
    tft.setCursor(55, 60);
    tft.setTextSize(2);
    tft.print("555555");
    delay(1);
    tft.setCursor(55, 60);
    tft.setTextSize(2);
    tft.print("666666");
    delay(1);
    tft.setCursor(55, 60);
    tft.setTextSize(2);
    tft.print("777777");
    delay(1);
    tft.setCursor(55, 60);
    tft.setTextSize(2);
    tft.print("888888");
    delay(1);
    tft.setCursor(55, 60);
    tft.setTextSize(2);
    tft.print("999999");
    delay(1);
  }
}

void displaydBm(){
  if (fwdVoltageADS0 > interceptFwd){
    dtostrf(pwrdBmFWD, 0, 2, DisplayValuedBm);
    tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.setCursor(55, 95);
    tft.print(DisplayValuedBm);
  }
  else {
    tft.setTextColor(ST77XX_BLACK, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.setCursor(55, 95);
    tft.print(DisplayValuedBm);
  }
}

void mqttMessagesPwrSwr(){
  client.publish("TandemTor/swr", String(valueSWR).c_str());
  client.publish("TandemTor/fwd", String(fwdVoltageADS0, 0).c_str());
  client.publish("TandemTor/rev", String(refVoltageADS1, 0).c_str());
  client.publish("TandemTor/fwdPwrVal", String(fwdPwrVal, 0).c_str());
  client.publish("TandemTor/fwdPwrValmW", String(fwdPwrVal, 4).c_str());
  client.publish("TandemTor/refPwrVal", String(refPwrVal, 0).c_str());
  client.publish("TandemTor/dBm FWD",String(pwrdBmFWD, 1).c_str());
}

void sendIPupdates() {
	static const unsigned long REFRESH_INTERVAL = 60000; // ms
		static unsigned long lastRefreshTime = 0;
		if(millis() - lastRefreshTime >= REFRESH_INTERVAL){
			lastRefreshTime = millis();
      Serial.print("IP address: "); Serial.println(WiFi.localIP());
		}
}

void sendStatusUpdates() {
	static const unsigned long REFRESH_INTERVAL = 150; // ms
		static unsigned long lastRefreshTime = 0;
		if(millis() - lastRefreshTime >= REFRESH_INTERVAL){
			lastRefreshTime = millis();
      calcSWR();
      calcPwrAD8310();
      displaySWRvalue();
      displayPvalue();
      displayPvaluemW();
      displaydBm();   
      mqttMessagesPwrSwr();
		}
}

void loop() {
  ArduinoOTA.handle();		// Comment if there is no WiFi requirement
  //syslogDebugLoop();
  adcLoop();
  sendStatusUpdates();		// Comment if there is no WiFi requirement
  sendIPupdates();		// Comment if there is no WiFi requirement
  client.loop();                // Comment if there is no WiFi requirement
    if (!client.connected()) {	// Comment if there is no WiFi requirement	
      connectMQTT();		// Comment if there is no WiFi requirement
    }				// Comment if there is no WiFi requirement
} 
