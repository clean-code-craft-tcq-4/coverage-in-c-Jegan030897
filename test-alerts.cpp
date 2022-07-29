#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = PASSIVE_COOLING;
  batteryChar.brand = LI_ION_BATTERY;
  
  checkAndAlert(batteryChar, -5, sendToController_forTesting);
  REQUIRE(breachType == TOO_LOW);
  
  checkAndAlert(batteryChar, 35, sendToEmail_forTesting);
  REQUIRE(breachType == NORMAL);
  
  checkAndAlert(batteryChar, 39, sendToEmail_forTesting);
  REQUIRE(breachType == TOO_HIGH);
  
  checkAndAlert(batteryChar, -7, sendToEmail_forTesting);
  REQUIRE(breachType == TOO_LOW);
  
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  checkAndAlert(batteryChar, 40, sendToEmail_forTesting);
  REQUIRE(breachType == NORMAL);
  
  checkAndAlert(batteryChar, 44, sendToEmail_forTesting);
  REQUIRE(breachType == TOO_HIGH);
  
  checkAndAlert(batteryChar, -1, sendToEmail_forTesting);
  REQUIRE(breachType == TOO_LOW);
  
  batteryChar.coolingType = HI_ACTIVE_COOLING;
  checkAndAlert(batteryChar, 45, sendToEmail_forTesting);
  REQUIRE(breachType == NORMAL);
  
  checkAndAlert(batteryChar, 46, sendToEmail_forTesting);
  REQUIRE(breachType == TOO_HIGH);
  
  checkAndAlert(batteryChar, -5, sendToEmail_forTesting);
  REQUIRE(breachType == TOO_LOW);
}
