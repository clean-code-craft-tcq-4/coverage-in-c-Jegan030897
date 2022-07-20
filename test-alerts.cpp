#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(20, 30, 35) == TOO_LOW);
  REQUIRE(inferBreach(36, 30, 35) == TOO_HIGH);
  REQUIRE(inferBreach(35, 30, 35) == NORMAL);
  REQUIRE(inferBreach(30, 30, 35) == NORMAL);
  REQUIRE(inferBreach(32, 30, 35) == NORMAL);
  REQUIRE(inferBreach(32, 41, 45) == TOO_LOW);
  REQUIRE(inferBreach(46, 41, 45) == TOO_HIGH);
  REQUIRE(inferBreach(42, 41, 45) == NORMAL);
  REQUIRE(inferBreach(41, 41, 45) == NORMAL);
  REQUIRE(inferBreach(45, 41, 45) == NORMAL);
  REQUIRE(inferBreach(32, 36, 40) == TOO_LOW);
  REQUIRE(inferBreach(46, 36, 40) == TOO_HIGH);
  REQUIRE(inferBreach(38, 36, 40) == NORMAL);
  REQUIRE(inferBreach(36, 36, 40) == NORMAL);
  REQUIRE(inferBreach(40, 36, 40) == NORMAL);
}

TEST_CASE("classify the breach according to limits") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = PASSIVE_COOLING;
  REQUIRE(classifyTemperatureBreach(batteryChar, 20) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(batteryChar, 36) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(batteryChar, 35) == NORMAL);
  REQUIRE(classifyTemperatureBreach(batteryChar, 30) == NORMAL);
  REQUIRE(classifyTemperatureBreach(batteryChar, 32) == NORMAL);
  
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  REQUIRE(classifyTemperatureBreach(batteryChar, 20) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(batteryChar, 36) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(batteryChar, 35) == NORMAL);
  REQUIRE(classifyTemperatureBreach(batteryChar, 30) == NORMAL);
  REQUIRE(classifyTemperatureBreach(batteryChar, 32) == NORMAL);
}

