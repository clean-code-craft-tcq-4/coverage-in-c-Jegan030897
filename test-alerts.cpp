#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = PASSIVE_COOLING;
  batteryChar.brand = LI_ION_BATTERY;
  
  checkAndAlert(TO_CONTROLLER, batteryChar, -5, SW_FOR_TESTING);
  REQUIRE(breachType == TOO_LOW);
  
  checkAndAlert(TO_EMAIL, batteryChar, 35, SW_FOR_TESTING);
  REQUIRE(breachType == NORMAL);
  
  checkAndAlert(TO_EMAIL, batteryChar, 39, SW_FOR_TESTING);
  REQUIRE(breachType == TOO_HIGH);
  
  checkAndAlert(TO_EMAIL, batteryChar, -7, SW_FOR_TESTING);
  REQUIRE(breachType == TOO_LOW);
  
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  checkAndAlert(TO_EMAIL, batteryChar, 40, SW_FOR_TESTING);
  REQUIRE(breachType == NORMAL);
  
  checkAndAlert(TO_EMAIL, batteryChar, 44, SW_FOR_TESTING);
  REQUIRE(breachType == TOO_HIGH);
  
  checkAndAlert(TO_EMAIL, batteryChar, -1, SW_FOR_TESTING);
  REQUIRE(breachType == TOO_LOW);
  
  batteryChar.coolingType = HI_ACTIVE_COOLING;
  checkAndAlert(TO_EMAIL, batteryChar, 45, SW_FOR_TESTING);
  REQUIRE(breachType == NORMAL);
  
  checkAndAlert(TO_EMAIL, batteryChar, 46, SW_FOR_TESTING);
  REQUIRE(breachType == TOO_HIGH);
  
  checkAndAlert(TO_EMAIL, batteryChar, -5, SW_FOR_TESTING);
  REQUIRE(breachType == TOO_LOW);
}
