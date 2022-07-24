#include "typewise-alert.h"
#include <stdio.h>

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

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC, swType getSWtype) {
  BreachType breachType = classifyTemperatureBreach(batteryChar, temperatureInC);
  
  void (*selectSW[NUMBER_OF_SW])(BreachType, AlertTarget) = {swforProduction, swforTesting};
  selectSW[getSWtype](breachType, alertTarget);
}

void swforProduction(BreachType breachType, AlertTarget alertTarget)
{
  if(TO_CONTROLLER == alertTarget){
    sendToController(breachType);
  }else {
    sendToEmail(breachType);
  }
}

void swforTesting(BreachType breachType, AlertTarget alertTarget)
{
  if(TO_CONTROLLER == alertTarget){
    sendToController(breachType);
  }else {
    sendToEmail(breachType);
  }
}

void sendToController(BreachType breachType) {
  SEND_MSG_TO_CONTROLLER(breachType);
}

void sendToEmail(BreachType breachType) {
  SEND_MSG_THROUGH_EMAIL(breachType);
}
