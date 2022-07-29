#include "typewise-alert.h"
#include <stdio.h>

BreachType breachType;

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

void checkAndAlert(BatteryCharacter batteryChar, double temperatureInC, void (*alterType) (BreachType getbreachType)) {
  breachType = classifyTemperatureBreach(batteryChar, temperatureInC);
  
  (*alterType) (breachType);
}

void sendToController_forTesting(BreachType getbreachType) {
  SEND_MSG_TO_CONTROLLER(getbreachType);
}

void sendToEmail_forTesting(BreachType getbreachType) {
  SEND_MSG_THROUGH_EMAIL(getbreachType); 
}

void sendToController(BreachType getbreachType) {
  //will be processed in real time hw setup
  SEND_MSG_TO_CONTROLLER(getbreachType);
}

void sendToEmail(BreachType getbreachType) {
  //will be processed in real time
  SEND_MSG_THROUGH_EMAIL(getbreachType);
}
