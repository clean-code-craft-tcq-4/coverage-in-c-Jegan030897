#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(20, 30, 35) == TOO_LOW);
  REQUIRE(inferBreach(36, 30, 35) == TOO_HIGH);
  REQUIRE(inferBreach(35, 30, 35) == NORMAL);
  REQUIRE(inferBreach(30, 30, 35) == NORMAL);
}

TEST_CASE("classify passive cooling limits") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = PASSIVE_COOLING;
  REQUIRE(classifyTemperatureBreach(batteryChar, 20) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(batteryChar, 36) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(batteryChar, 35) == NORMAL);
  REQUIRE(classifyTemperatureBreach(batteryChar, 30) == NORMAL);
  REQUIRE(classifyTemperatureBreach(batteryChar, 32) == NORMAL);
}

TEST_CASE("classify med active cooling limits") {
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  REQUIRE(classifyTemperatureBreach(batteryChar, 20) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(batteryChar, 36) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(batteryChar, 35) == NORMAL);
  REQUIRE(classifyTemperatureBreach(batteryChar, 30) == NORMAL);
  REQUIRE(classifyTemperatureBreach(batteryChar, 32) == NORMAL);
}

