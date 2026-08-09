#include "SscmaI2CDriver.h"
#include <Wire.h>

SscmaI2CDriver::SscmaI2CDriver() : _ready(false) {}

bool SscmaI2CDriver::begin() {
    Wire.begin();
    if (!_ai.begin(&Wire)) {
        _ready = false;
        return false;
    }
    _ready = true;
    return true;
}

bool SscmaI2CDriver::isConnected() {
    return _ready;
}

bool SscmaI2CDriver::reset() {
    _ready = false;
    return begin();
}

bool SscmaI2CDriver::read(VisionResult &result) {
    memset(&result, 0, sizeof(VisionResult));

    if (!_ready) {
        result.connected = false;
        result.success = false;
        return false;
    }

    uint32_t startTime = millis();

    if (!_ai.invoke()) {
        result.connected = true;
        result.success = false;
        return false;
    }

    result.inferenceMs = millis() - startTime;
    result.connected = true;
    result.success = true;

    VisionResultConverter::convert(_ai, result);

    return true;
}