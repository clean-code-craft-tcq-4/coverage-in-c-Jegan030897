#pragma once

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
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

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

#define PASSIVE_COOLING_LOW_LIMIT          30
#define PASSIVE_COOLING_HIGH_LIMIT         35
#define HI_ACTIVE_COOLING_LOW_LIMIT        41
#define HI_ACTIVE_COOLING_HIGH_LIMIT       45
#define MED_ACTIVE_COOLING_LOW_LIMIT       36
#define MED_ACTIVE_COOLING_HIGH_LIMIT       40

#define checkBreach(currentvalue, lowerLimit, upperLimit)
(
  BreachType currentBreach = NORMAL;
  if(value < lowerLimit) {
     currentBreach = TOO_LOW;
  }
  if(value > upperLimit) {
    currentBreach = TOO_HIGH;
  }
)

void checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
