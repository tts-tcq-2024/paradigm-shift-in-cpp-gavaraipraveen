#include <assert.h>
#include <iostream>
#include <string>
#include <tuple>
using namespace std;

struct CheckResult {
  bool isOk;
  string message;
};

// Function to check temperature
CheckResult checkTemperature(float temperature) {
  if (temperature < 0) {
    return {false, "Temperature too low!"};
  } else if (temperature > 45) {
    return {false, "Temperature too high!"};
  }
  return {true, ""};
}

// Function to check state of charge (SOC)
CheckResult checkSoc(float soc) {
  if (soc < 20) {
    return {false, "State of Charge too low!"};
  } else if (soc > 80) {
    return {false, "State of Charge too high!"};
  }
  return {true, ""};
}

// Function to check charge rate
CheckResult checkChargeRate(float chargeRate) {
  if (chargeRate > 0.8) {
    return {false, "Charge Rate too high!"};
  }
  return {true, ""};
}

// Function to check all parameters
bool batteryIsOk(float temperature, float soc, float chargeRate) {
  auto tempResult = checkTemperature(temperature);
  auto socResult = checkSoc(soc);
  auto chargeRateResult = checkChargeRate(chargeRate);

  if (!tempResult.isOk) {
    cout << tempResult.message << "\n";
    return false;
  }
  if (!socResult.isOk) {
    cout << socResult.message << "\n";
    return false;
  }
  if (!chargeRateResult.isOk) {
    cout << chargeRateResult.message << "\n";
    return false;
  }

  return true;
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
