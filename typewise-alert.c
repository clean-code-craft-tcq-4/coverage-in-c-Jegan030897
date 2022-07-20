#include "typewise-alert.h"
#include <stdio.h>

char Battery_TempLimit[NUMBER_OF_BATTERY_TYPE][NUMBER_OF_BATTERY_TYPE][6] = 
{PASSIVE_COOLING_LOW_LIMIT,  PASSIVE_COOLING_HIGH_LIMIT,  MED_ACTIVE_COOLING_LOW_LIMIT,  MED_ACTIVE_COOLING_HIGH_LIMIT,  HI_ACTIVE_COOLING_LOW_LIMIT,  HI_ACTIVE_COOLING_HIGH_LIMIT};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  return checkBreach(value, lowerLimit, upperLimit);
}

BreachType classifyTemperatureBreach(BatteryCharacter batteryChar, double temperatureInC) {
  return inferBreach(temperatureInC, Battery_TempLimit[batteryChar.brand][batteryChar.brand][batteryChar.coolingType], Battery_TempLimit[batteryChar.brand][batteryChar.brand][batteryChar.coolingType+1]);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
  BreachType breachType = classifyTemperatureBreach(batteryChar, temperatureInC);
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
