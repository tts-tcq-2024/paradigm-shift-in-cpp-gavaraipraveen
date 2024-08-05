#include <assert.h>
#include <iostream>
#include <string>

using namespace std;

// Enumeration for languages
enum Language { ENGLISH, GERMAN };

// Global variable to set the language
Language currentLanguage = ENGLISH;

// Structure to hold thresholds
struct ParameterThresholds {
    float lowerLimit;
    float upperLimit;
    float warningTolerance;
};

// Function to translate messages
string translateMessage(const string& english, const string& german) {
    return (currentLanguage == ENGLISH) ? english : german;
}

// Function to get warning message
string getWarningMessage(const string& approachingDischarge, const string& approachingChargePeak) {
    return translateMessage(approachingDischarge, approachingChargePeak);
}

// Function to get status message for below limit
string getBelowLimitMessage(const string& parameterName) {
    return translateMessage(parameterName + " is too low!", parameterName + " ist zu niedrig!");
}

// Function to get status message for above limit
string getAboveLimitMessage(const string& parameterName) {
    return translateMessage(parameterName + " is too high!", parameterName + " ist zu hoch!");
}

// Function to check status for below limit
bool checkBelowLimit(float value, const ParameterThresholds& thresholds) {
    return value < thresholds.lowerLimit;
}

// Function to check status for warning range below
bool checkWarningRangeBelow(float value, const ParameterThresholds& thresholds) {
    return value >= thresholds.lowerLimit && value < thresholds.lowerLimit + thresholds.warningTolerance;
}

// Function to check status for warning range above
bool checkWarningRangeAbove(float value, const ParameterThresholds& thresholds) {
    return value >= thresholds.upperLimit - thresholds.warningTolerance && value < thresholds.upperLimit;
}

// Function to check status for above limit
bool checkAboveLimit(float value, const ParameterThresholds& thresholds) {
    return value > thresholds.upperLimit;
}

// Function to generate the parameter status message
string getParameterStatusMessage(float value, const ParameterThresholds& thresholds, const string& parameterName) {
    if (checkBelowLimit(value, thresholds)) {
        return getBelowLimitMessage(parameterName);
    }
    if (checkWarningRangeBelow(value, thresholds)) {
        return getWarningMessage("Warning: Approaching discharge", "Warnung: Nahe der Entladung");
    }
    if (checkWarningRangeAbove(value, thresholds)) {
        return getWarningMessage("Warning: Approaching charge-peak", "Warnung: Nahe der Ladespitze");
    }
    if (checkAboveLimit(value, thresholds)) {
        return getAboveLimitMessage(parameterName);
    }
    return translateMessage(parameterName + " is normal", parameterName + " ist normal");
}

// Function to check temperature
string checkTemperature(float temperature) {
    ParameterThresholds temperatureThresholds = {0, 45, 2.25};  // 5% of 45
    return getParameterStatusMessage(temperature, temperatureThresholds, "Temperature");
}

// Function to check state of charge (SOC)
string checkSoc(float soc) {
    ParameterThresholds socThresholds = {20, 80, 4};  // 5% of 80
    return getParameterStatusMessage(soc, socThresholds, "SOC");
}

// Function to check charge rate
string checkChargeRate(float chargeRate) {
    ParameterThresholds chargeRateThresholds = {0, 0.8, 0.04};  // 5% of 0.8
    return getParameterStatusMessage(chargeRate, chargeRateThresholds, "Charge rate");
}

// Function to check if each parameter is ok
bool isParameterOk(float value, const ParameterThresholds& thresholds) {
    return !(checkBelowLimit(value, thresholds) || checkAboveLimit(value, thresholds));
}

// Function to check all parameters
bool batteryIsOk(float temperature, float soc, float chargeRate) {
    ParameterThresholds temperatureThresholds = {0, 45, 2.25};
    ParameterThresholds socThresholds = {20, 80, 4};
    ParameterThresholds chargeRateThresholds = {0, 0.8, 0.04};

    cout << checkTemperature(temperature) << endl;
    cout << checkSoc(soc) << endl;
    cout << checkChargeRate(chargeRate) << endl;

    return isParameterOk(temperature, temperatureThresholds) &&
           isParameterOk(soc, socThresholds) &&
           isParameterOk(chargeRate, chargeRateThresholds);
}

// Function to run tests
void runTests() {
    currentLanguage = ENGLISH;  // Test in English
    assert(batteryIsOk(25, 70, 0.7) == true);
    assert(batteryIsOk(-5, 70, 0.7) == false);
    assert(batteryIsOk(50, 70, 0.7) == false);
    assert(batteryIsOk(25, 10, 0.7) == false);
    assert(batteryIsOk(25, 85, 0.7) == false);
    assert(batteryIsOk(25, 70, 0.9) == false);

    currentLanguage = GERMAN;  // Test in German
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
    return 0;
}
