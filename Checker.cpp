#include <assert.h>
#include <iostream>
#include <string>
#include <tuple>
using namespace std;

// Function to check temperature
bool checkTemperature(float temperature) {
    return temperature < 0 || temperature > 45;
}

// Function to check state of charge (SOC)
bool checkSoc(float soc) {
    return soc < 20 || soc > 80;
}

// Function to check charge rate
bool checkChargeRate(float chargeRate) {
    return chargeRate > 0.8;
}

// Function to check all parameters
bool batteryIsOk(float temperature, float soc, float chargeRate) {
  return !checkTemperature(temperature) &&
         !checkSoc(soc) &&
         !checkChargeRate(chargeRate);
}

// Function to run tests
void runTests() {
  assert(batteryIsOk(25, 70, 0.7) == true);
  assert(batteryIsOk(-5, 70, 0.7) == false);
  assert(batteryIsOk(50, 70, 0.7) == false);
  assert(batteryIsOk(25, 10, 0.7) == false);
  assert(batteryIsOk(25, 85, 0.7) == false);
  assert(batteryIsOk(25, 70, 0.9) == false);
}

int main() {
  runTests();
  cout << "All tests passed.\n";
}
