/**
 * 
 * ESP32-based 2KW SWR/Power meter AD8310 based
 * Project description http://vk6nx.net/06_projects.html
 * Source code: http://github.com/VK6NX/
 * 
 * 
 */

#ifndef MQTTINIT_H_
#define MQTTINIT_H_

#include <MQTT.h>

#include <ArduinoJson.h>              // Json lib
#include "mainconfig.h" 
#include "wifinit.h"

MQTTClient client(1024);

StaticJsonDocument<1024> doc1;
//DynamicJsonDocument doc1(2048);

void json_pub(){
  String output1;
  doc1.clear();
  serializeJson(doc1, output1);
  client.publish(String(mqttNAME)+"/fullState", output1); 
}

void connectMQTT() {
  Serial.print("\nconnectMQTT checking WiFi ");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    delay(1000);
  }

  Serial.print("\nconnecting to MQTT broker");
  while (!client.connect(mqttNAME, "", "")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nMQTT connected");

  client.subscribe("ATUconn/#");

}

void mqttPingResponse(){
  String output2;
  doc1.clear();
  doc1["TuningStatus"] = "READY";
  serializeJson(doc1, output2);
  client.publish(String(mqttNAME)+"/fullState", output2);
}


void wifiMqttInit() {
  WiFi.setTxPower(WIFI_POWER_19_5dBm);
  WiFi.begin(ssid, pass);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported
  // Set the IP address directly.
  client.begin(mqttHOST, net);
  connectMQTT();
}

#endif /* MQTTINIT_H_ */
