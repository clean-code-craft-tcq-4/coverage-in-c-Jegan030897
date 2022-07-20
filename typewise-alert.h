#pragma once

typedef enum {
  PASSIVE_COOLING = 0,
  HI_ACTIVE_COOLING = 2,
  MED_ACTIVE_COOLING = 4,
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
  char brand[48];
} BatteryCharacter;

#define HEADER                              0xfeed
#define RECEPIENT                           "a.b@c.com"

#define PASSIVE_COOLING_LOW_LIMIT           30
#define PASSIVE_COOLING_HIGH_LIMIT          35
#define HI_ACTIVE_COOLING_LOW_LIMIT         41
#define HI_ACTIVE_COOLING_HIGH_LIMIT        45
#define MED_ACTIVE_COOLING_LOW_LIMIT        36
#define MED_ACTIVE_COOLING_HIGH_LIMIT       40

#define checkBreach(currentvalue, lowerLimit, upperLimit)   \
({                                                          \
  BreachType currentBreach = NORMAL;                        \
  if (value < lowerLimit) {                                 \
     currentBreach = TOO_LOW;                               \
  }else if (value > upperLimit) {                           \
    currentBreach = TOO_HIGH;                               \
  }else {                                                   \
  }                                                         \
  currentBreach;                                            \
})                                                          \

#define SEND_MSG_TO_CONTROLLER(breachType)                  \
({                                                          \
  printf("%x : %x\n", HEADER, breachType);                  \
})                                                          \  

#define SEND_MSG_THROUGH_EMAIL(breachType)                  \
({                                                          \
  if (TOO_LOW == breachType) {                              \
    printf("To: %s\n", RECEPIENT);                          \
    printf("Hi, the temperature is too low\n");             \
  }else if (TOO_HIGH == breachType) {                       \
    printf("To: %s\n", RECEPIENT);                          \
    printf("Hi, the temperature is too high\n");            \
  }else {                                                   \
    /* nothing to do */                                     \
  }                                                         \
})                                                          \

void checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(BatteryCharacter batteryChar, double temperatureInC);

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
