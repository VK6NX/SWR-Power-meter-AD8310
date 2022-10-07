/**
 * 
 * ESP32-based 2KW SWR/Power meter AD8310 based
 * Project description http://vk6nx.net/06_projects.html
 * Source code: http://github.com/VK6NX/PAcontrol
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

// MQTT-based triggers
void messageReceived(String &topic, String &payload) {
  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.

//Serial.println("MQTT in: " + topic + " - " + payload);

//EXAMPLES
/*
  if (topic == "ATUconn/atuPing"){
    if (payload == "1") {
      Serial.println("\nReceived ATUconn/atuPing");
      atuPing = true;
    }
  }
  
  if (topic == "ATUconn/Tune"){
    jsonTune(payload);
  }
*/
}

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
  //Serial.println("\nTuning Status: READY published");
}

void mqttMessages(){
  String output;
  doc1.clear();
  /*
  doc1["valueSWR"] = valueSWR;
  doc1["fwdPwrVal"] = fwdPwrVal;
  doc1["refPwrVal"] = refPwrVal;
  doc1["fwdPwrDisplay"] = fwdPwrDisplay;
  doc1["rflPwrPercent"] = rflPwrPercent;
  doc1["FwdVoltageADS0mV"] = fwdVoltageADS0;
  doc1["RefVoltageADS1mV"] = revVoltageADS1;
  doc1["c1actualStep"] = String(C1value);
  doc1["c2actualStep"] = String(C2value);
  doc1["lactualStep"] = String(Lvalue);
  doc1["c1actualVal"] = String(actualC1pf, 0);
  doc1["c2actualVal"] = String(actualC2pf, 0);
  doc1["lactualVal"] = String(actualLuH, 2);
  doc1["PowerdBmFWD"] = pwrdBmFWD;
  */
  serializeJson(doc1, output);
  client.publish(String(mqttNAME)+"/fullState", output);
}

void wifiMqttInit() {
  WiFi.setTxPower(WIFI_POWER_19_5dBm);
  WiFi.begin(ssid, pass);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported
  // Set the IP address directly.
  client.begin(mqttHOST, net);
  client.onMessage(messageReceived);
  connectMQTT();
}

#endif /* MQTTINIT_H_ */
