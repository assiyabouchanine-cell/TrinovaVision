#include "SscmaUartDriver.h"

SscmaUartDriver::SscmaUartDriver() : _ready(false) {}

bool SscmaUartDriver::begin() {
    Serial1.begin(921600);

    if (!_ai.begin(&Serial1)) {
        _ready = false;
        return false;
    }
    _ready = true;
    return true;
}

bool SscmaUartDriver::isConnected() {
    return _ready;
}

bool SscmaUartDriver::reset() {
    _ready = false;
    return begin();
}

bool SscmaUartDriver::read(VisionResult &result) {
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