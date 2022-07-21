#pragma once
#include "string.h"

extern char getID[30];

typedef enum {
  PASSIVE_COOLING = 0,
  MED_ACTIVE_COOLING = 2,
  HI_ACTIVE_COOLING = 4,
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef enum {
  LI_ION_BATTERY,
  NUMBER_OF_BATTERY_TYPE
} BatteryType;

typedef struct {
  CoolingType coolingType;
  BatteryType brand;
} BatteryCharacter;

#define CONTROLLER_ID                       "0xfeed"
#define EMAIL_ID                            "ab@c.bsh.com"

#define PASSIVE_COOLING_LOW_LIMIT           30
#define PASSIVE_COOLING_HIGH_LIMIT          35
#define HI_ACTIVE_COOLING_LOW_LIMIT         41
#define HI_ACTIVE_COOLING_HIGH_LIMIT        45
#define MED_ACTIVE_COOLING_LOW_LIMIT        36
#define MED_ACTIVE_COOLING_HIGH_LIMIT       40

#define checkBreach(currentvalue, lowerLimit, upperLimit)               \
({                                                                      \
  BreachType currentBreach = NORMAL;                                    \
  if (value < lowerLimit) {                                             \
     currentBreach = TOO_LOW;                                           \
  }else if (value > upperLimit) {                                       \
    currentBreach = TOO_HIGH;                                           \
  }else {                                                               \
  }                                                                     \
  currentBreach;                                                        \
})                                                                      \

#define SEND_MSG_TO_CONTROLLER(breachType)                              \
({                                                                      \
  sprintf(getID,"%s",CONTROLLER_ID);                                    \
  printf("%s", getID);                                                  \
  printf(": %x\n", breachType);                                         \
})                                                                      \  

#define SEND_MSG_THROUGH_EMAIL(breachType)                              \
({                                                                      \
  sprintf(getID,"%s",EMAIL_ID);                                         \
  if (TOO_LOW == breachType) {                                          \
    printf("%s", getID);                                                \                          
    printf("Hi, the temperature is too low\n");                         \
  }else if (TOO_HIGH == breachType) {                                   \
    printf("%s", getID);                                                \                         
    printf("Hi, the temperature is too high\n");                        \
  }else {                                                               \                        
    /* nothing to do */                                                 \
  }                                                                     \
})                                                                      \

void checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(BatteryCharacter batteryChar, double temperatureInC);

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
