#include "typewise-alert.h"
#include <stdio.h>

Battery_TempLimit[NUMBER_OF_BATTERY_TYPE][NUMBER_OF_BATTERY_TYPE][6] = 
{PASSIVE_COOLING_LOW_LIMIT,  PASSIVE_COOLING_HIGH_LIMIT,  MED_ACTIVE_COOLING_LOW_LIMIT,  MED_ACTIVE_COOLING_HIGH_LIMIT,  HI_ACTIVE_COOLING_LOW_LIMIT,  HI_ACTIVE_COOLING_HIGH_LIMIT};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  return checkBreach(value, lowerLimit, upperLimit);
}

BreachType classifyTemperatureBreach(BatteryCharacter batteryChar, double temperatureInC) {
  return inferBreach(temperatureInC, Battery_TempLimit[batteryChar.brand][batteryChar.brand][batteryChar.coolingType], Battery_TempLimit[batteryType_e][batteryType_e][batteryChar.coolingType+1]);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
  BreachType breachType = classifyTemperatureBreach(batteryChar, temperatureInC);
  
  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  switch(breachType) {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      break;
    case NORMAL:
      break;
  }
}
