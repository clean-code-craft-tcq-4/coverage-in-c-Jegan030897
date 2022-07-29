#pragma once
#include "string.h"

typedef enum {
  SW_FOR_PRODUCTION,
  SW_FOR_TESTING,
  NUMBER_OF_SW
} swType;

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

extern BreachType breachType;

#define CONTROLLER_ID                       0xfeed
#define EMAIL_ID                            "ab.com"

#define PASSIVE_COOLING_LOW_LIMIT           0
#define PASSIVE_COOLING_HIGH_LIMIT          35
#define HI_ACTIVE_COOLING_LOW_LIMIT         0
#define HI_ACTIVE_COOLING_HIGH_LIMIT        45
#define MED_ACTIVE_COOLING_LOW_LIMIT        0
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
  printf("%x: %x\n",CONTROLLER_ID, breachType);                         \
})                                                                      \  

#define SEND_MSG_THROUGH_EMAIL(breachType)                              \
({                                                                      \
  printf("%s\n",EMAIL_ID);                                              \
  if (TOO_LOW == breachType) {                                          \                        
    printf("Hi, the temperature is too low\n");                         \
  }else if (TOO_HIGH == breachType) {                                   \                        
    printf("Hi, the temperature is too high\n");                        \
  }else {                                                               \                        
    /* nothing to do */                                                 \
  }                                                                     \
})                                                                      \

void checkAndAlert(BatteryCharacter batteryChar, double temperatureInC, void (*alterType) (BreachType getbreachType));

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(BatteryCharacter batteryChar, double temperatureInC);

void sendToController(BreachType getbreachType);
void sendToEmail(BreachType getbreachType);
void sendToController_forTesting(BreachType getbreachType);
void sendToEmail_forTesting(BreachType getbreachType);
