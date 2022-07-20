#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"
#include "string.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(20, 30, 35) == TOO_LOW);
  REQUIRE(inferBreach(36, 30, 35) == TOO_HIGH);
  REQUIRE(inferBreach(35, 30, 35) == NORMAL);
  REQUIRE(inferBreach(30, 30, 35) == NORMAL);
}

TEST_CASE("classify breach") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = PASSIVE_COOLING;
  batteryChar.brand = LI_ION_BATTERY;
  REQUIRE(classifyTemperatureBreach(batteryChar, -5) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(batteryChar, 36) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(batteryChar, 35) == NORMAL);
  REQUIRE(classifyTemperatureBreach(batteryChar, 30) == NORMAL);
  REQUIRE(classifyTemperatureBreach(batteryChar, 32) == NORMAL);
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  REQUIRE(classifyTemperatureBreach(batteryChar, -1) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(batteryChar, 41) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(batteryChar, 36) == NORMAL);
  batteryChar.coolingType = HI_ACTIVE_COOLING ;
  REQUIRE(classifyTemperatureBreach(batteryChar, 35) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(batteryChar, 55) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(batteryChar, 45) == NORMAL);
}

TEST_CASE("send email") {
  sendToController(TOO_LOW);
  SEND_MSG_TO_CONTROLLER(getControllerID, strlen(getControllerID), TOO_LOW);
  for(int i; i< (int)strlen(getControllerID); i++)
    REQUIRE(strcmp(*(getControllerID+i), *(receiveControllerID+i) == 0));
  
}
