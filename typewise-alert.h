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


void checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(BatteryCharacter batteryChar, double temperatureInC);

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
