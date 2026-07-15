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

    convertToVisionResult(result);

    return true;
}

void SscmaI2CDriver::convertToVisionResult(VisionResult &result) {
    uint8_t n = _ai.boxes().size();
    if (n > TRINOVA_MAX_OBJECTS) {
        n = TRINOVA_MAX_OBJECTS;
    }

    result.count = n;
    result.detected = (n > 0);

    for (uint8_t i = 0; i < n; i++) {
        result.objects[i].classId = _ai.boxes()[i].target;
        result.objects[i].confidence = _ai.boxes()[i].score;
        result.objects[i].x = _ai.boxes()[i].x;
        result.objects[i].y = _ai.boxes()[i].y;
        result.objects[i].width = _ai.boxes()[i].w;
        result.objects[i].height = _ai.boxes()[i].h;

        snprintf(result.objects[i].label, sizeof(result.objects[i].label),
                 "class_%d", result.objects[i].classId);
    }
}