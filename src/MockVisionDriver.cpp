#include "MockVisionDriver.h"
#include <string.h>

MockVisionDriver::MockVisionDriver()
    : _ready(false), _scenario(MockScenario::PersonCenter) {}

bool MockVisionDriver::begin() {
    _ready = true;
    return true;
}

bool MockVisionDriver::isConnected() {
    return _ready && (_scenario != MockScenario::Disconnected);
}

bool MockVisionDriver::reset() {
    _ready = true;
    return true;
}

void MockVisionDriver::setScenario(MockScenario scenario) {
    _scenario = scenario;
}

bool MockVisionDriver::read(VisionResult &result) {
    memset(&result, 0, sizeof(VisionResult));
    result.preprocessMs  = 2;
    result.inferenceMs   = 15;
    result.postprocessMs = 1;

    if (!_ready) {
        result.connected = false;
        result.success = false;
        return false;
    }

    switch (_scenario) {
        case MockScenario::Disconnected:
            result.connected = false;
            result.success = false;
            return false;

        case MockScenario::Timeout:
            result.connected = true;
            result.success = false;
            return false;

        case MockScenario::PersonLeft:
            result.connected = true;
            fillPersonLeft(result);
            break;

        case MockScenario::PersonCenter:
            result.connected = true;
            fillPersonCenter(result);
            break;

        case MockScenario::NoDetection:
            result.connected = true;
            fillNoDetection(result);
            break;

        case MockScenario::MultipleObjects:
            result.connected = true;
            fillMultipleObjects(result);
            break;

        case MockScenario::LowConfidence:
            result.connected = true;
            fillLowConfidence(result);
            break;
        

        case MockScenario::Overflow:
            result.connected = true;
            fillOverflow(result);
            break;
    }

    result.success = true;
    return true;
}

void MockVisionDriver::fillPersonLeft(VisionResult &r) {
    r.detected = true;
    r.count = 1;
    r.objects[0].classId = 0;
    strncpy(r.objects[0].label, "person", sizeof(r.objects[0].label));
    r.objects[0].confidence = 92;
    r.objects[0].x = 50;
    r.objects[0].y = 90;
    r.objects[0].width = 40;
    r.objects[0].height = 80;
}

void MockVisionDriver::fillPersonCenter(VisionResult &r) {
    r.detected = true;
    r.count = 1;
    r.objects[0].classId = 0;
    strncpy(r.objects[0].label, "person", sizeof(r.objects[0].label));
    r.objects[0].confidence = 88;
    r.objects[0].x = 160;
    r.objects[0].y = 90;
    r.objects[0].width = 45;
    r.objects[0].height = 85;
}

void MockVisionDriver::fillNoDetection(VisionResult &r) {
    r.detected = false;
    r.count = 0;
}

void MockVisionDriver::fillMultipleObjects(VisionResult &r) {
    r.detected = true;
    r.count = 3;

    r.objects[0].classId = 0;
    strncpy(r.objects[0].label, "person", sizeof(r.objects[0].label));
    r.objects[0].confidence = 90;
    r.objects[0].x = 40; 
    r.objects[0].y = 60;
     r.objects[0].width = 30; 
     r.objects[0].height = 70;

    r.objects[1].classId = 1;
    strncpy(r.objects[1].label, "bottle", sizeof(r.objects[1].label));
    r.objects[1].confidence = 75;
    r.objects[1].x = 120;
     r.objects[1].y = 100; 
     r.objects[1].width = 15;
      r.objects[1].height = 40;

    r.objects[2].classId = 2;
    strncpy(r.objects[2].label, "chair", sizeof(r.objects[2].label));
    r.objects[2].confidence = 60;
    r.objects[2].x = 200;
     r.objects[2].y = 80; 
     r.objects[2].width = 50; 
     r.objects[2].height = 60;
}

void MockVisionDriver::fillLowConfidence(VisionResult &r) {
    r.detected = true;
    r.count = 1;
    r.objects[0].classId = 3;
    strncpy(r.objects[0].label, "unknown", sizeof(r.objects[0].label));
    r.objects[0].confidence = 40;
    r.objects[0].x = 10; 
    r.objects[0].y = 10; 
    r.objects[0].width = 20; 
    r.objects[0].height = 20;
}

 void MockVisionDriver::fillOverflow(VisionResult &r) {
    
    r.detected = true;
    r.count = TRINOVA_MAX_OBJECTS;  

    for (uint8_t i = 0; i < TRINOVA_MAX_OBJECTS; i++) {
        r.objects[i].classId = i;
        strncpy(r.objects[i].label, "object", sizeof(r.objects[i].label));
        r.objects[i].confidence = 70;
        r.objects[i].x = i * 10;
        r.objects[i].y = 0;
        r.objects[i].width = 10;
        r.objects[i].height = 10;
    }
}