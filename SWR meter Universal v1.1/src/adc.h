/*
 * adc.h for ADS1115
 * Project description http://vk6nx.net/06_projects.html
 * Source: code https://github.com/VK6NX/SWR-Power-meter-AD8310
 * 
 * by VK6NX & VK3FDMI (aka ziss)
 *
 * ADS1115 library ADS1115_WE by Wolfgang Ewald
 * https://github.com/wollewald/ADS1115_WE     
 *      
 *  IMPORTANT - make sure you have external libraries versions line up.
 * 
 */
 
#ifndef ADC_H_
#define ADC_H_

#include "mainconfig.h" 
#include<ADS1115_WE.h> 
#include<Wire.h>
#define I2C_ADDRESS 0x48

ADS1115_WE adc = ADS1115_WE(I2C_ADDRESS);

volatile bool convReady = false;

uint16_t adcCnt = 0;
ADS1115_MUX adcChannel = ADS1115_COMP_0_GND;

inline void adcInit() {
  pinMode(alertReadyPin, INPUT_PULLUP);
  Wire.begin();
  if(!adc.init()){
    Serial.println("ADS1115 not connected!");
  }
  adc.setVoltageRange_mV(ADS1115_RANGE_4096);

  adc.setCompareChannels(adcChannel);
  adc.setConvRate(ADS1115_128_SPS);
  adc.setMeasureMode(ADS1115_SINGLE);
  adc.setAlertPinMode(ADS1115_ASSERT_AFTER_1);
  adc.setAlertPinToConversionReady();
  adc.startSingleMeasurement();
}


inline void adcLoop() {
  //if (!adc.isBusy()) {                      // alternative if alertReadyPin config does not work on any reason
  if (digitalRead(alertReadyPin) != HIGH) {
    if (adcChannel == ADS1115_COMP_0_GND){
      fwdVoltageADS0 = adc.getResult_mV();
      adcChannel = ADS1115_COMP_1_GND;
      if (fwdPwrPeakVal < fwdVoltageADS0) {
          fwdPwrPeakVal = fwdVoltageADS0;
      }
    } 
    else {       
        refVoltageADS1 = adc.getResult_mV();
        adcChannel = ADS1115_COMP_0_GND;
    }
    adc.setCompareChannels(adcChannel);
    adc.startSingleMeasurement();
     rflPwrPercent = (refVoltageADS1 / fwdVoltageADS0);
    adcCnt++; 
  }
}

void calcPwrAD8310() {
  if (fwdVoltageADS0 < interceptFwd){ // cosmetic function for ATUCconnect displays 
    fwdPwrVal = 0; // cosmetic value
    refPwrVal = 0; // cosmetic value
  }
  else{
    fwdPwrVal =  exp((fwdVoltageADS0 - 1825.758513)/97.307272);
    refPwrVal = exp((refVoltageADS1 - 1851.98376)/95.01818);
    pwrdBmFWD = 10 * log10(1000 * fwdPwrVal); 
  }
}

void calcSWR() {
  float p = (refPwrVal / fwdPwrVal);
  float swr = (1 + p) / (1 - p);
  if (fwdVoltageADS0 < interceptFwd){ // cosmetic function for ATUCconnect displays 
    valueSWR = 0; // cosmetic value
  }
  else {
    if (swr != valueSWR) {
      valueSWR = (1 + p) / (1 - p);
    }
  }
}

inline uint8_t adcLpfRaiseCnt() {
  return adcTickCount;
}

#endif /* ADC_H_ */
