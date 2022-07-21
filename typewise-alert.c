#include "typewise-alert.h"
#include <stdio.h>

char *getControllerID;
char *getuseremailID;
char *receiveControllerID;
char *receiveuseremailID;

int Battery_TempLimit[NUMBER_OF_BATTERY_TYPE][6] = 
{PASSIVE_COOLING_LOW_LIMIT,  PASSIVE_COOLING_HIGH_LIMIT,  MED_ACTIVE_COOLING_LOW_LIMIT,  MED_ACTIVE_COOLING_HIGH_LIMIT,  HI_ACTIVE_COOLING_LOW_LIMIT,  HI_ACTIVE_COOLING_HIGH_LIMIT};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  return checkBreach(value, lowerLimit, upperLimit);
}

BreachType classifyTemperatureBreach(BatteryCharacter batteryChar, double temperatureInC) {
  int LowLimit = batteryChar.coolingType;
  int UpperLimit = LowLimit + 1;
  int BatteryBrand = batteryChar.brand;
  return inferBreach(temperatureInC, Battery_TempLimit[BatteryBrand][LowLimit], Battery_TempLimit[BatteryBrand][UpperLimit]);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
  BreachType breachType = classifyTemperatureBreach(batteryChar, temperatureInC);
  if(TO_CONTROLLER == alertTarget){
    sendToController(breachType);
  }else {
    sendToEmail(breachType);
  }
}

void GetControllerID(void) {
  getControllerID = "0xfa10";
  sprintf(getControllerID,"%s",getID);
}

void GetuserEmailID(void) {
  char getID[] = "a.b@c.com";
  sprintf(getuseremailID,"%s",getID);
}

void sendToController(BreachType breachType) {
  GetControllerID();
  SEND_MSG_TO_CONTROLLER(getControllerID, strlen(getControllerID), breachType);
}

void sendToEmail(BreachType breachType) {
  GetuserEmailID();
  SEND_MSG_THROUGH_EMAIL(getuseremailID, strlen(getuseremailID), breachType);
}
