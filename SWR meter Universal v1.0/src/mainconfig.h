/**
 * 
 * ESP32-based 2KW SWR/Power meter AD8310 based
 * Project description http://vk6nx.net/06_projects.html
 * Source code: http://github.com/VK6NX/
 * 
 * 
 *
 *
 * mainconfig.h
 */

#ifndef MAINCONFIG_H_
#define MAINCONFIG_H_

#include <Arduino.h>
#include <Wire.h>

// ************** Syslog related parameters *******************


// *************** MQTT related parameters *********************
const char* mqttHOST = "192.168.1.50";  // MQTT Broker server ip

const char* mqttNAME = "TandemTor";   // Client name that uniquely identify device

// *************** ADC related parameters **********************

int alertReadyPin = 19;

float fwdVoltageADS0 = 0;       // a0
float refVoltageADS1 = 0;       // a1
float fwdPwrPeakVal = 0;   

float fwdPwrVal;
float fwdPwrDisplay;
float refPwrVal;
float pwrdBmFWD;

float valueSWR;

int interceptFwd = 1100; // calculated intercept for FWD
int interceptRef = 800; // calculated intercept for REF

float rflPwrPercent = 0;

int adcTickCount = 10; // number of ADC readings  for ADS1115_8_SPS
//int adcCntValue = 1000; // for ADS1115_250_SPS

// *************** TFT Display related parameters **********************
char DisplayValueSWR[4];
char DisplayValueP[4];
char DisplayValuePmW[0];
char DisplayValueFWD[4];
char DisplayValueREV[4];
char DisplayValuedBm[4];

// *************** Other / Test / Debug parameters ********************


#endif /* MAINCONFIG_H_ */
