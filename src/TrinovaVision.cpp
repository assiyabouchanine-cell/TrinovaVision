#include "TrinovaVision.h"
#include "MockVisionDriver.h"

TrinovaVision::TrinovaVision()
    : _driver(nullptr),
      _mode(VisionMode::Mock),
      _confidenceThreshold(0),
      _lastError(TrinovaError::None),
      _totalReads(0),
      _consecutiveErrors(0) {}

TrinovaVision::~TrinovaVision() {
    if (_driver) {
        delete _driver;
        _driver = nullptr;
    }
}

bool TrinovaVision::begin(VisionMode mode) {
    _mode = mode;

    if (_driver) {
        delete _driver;
        _driver = nullptr;
    }

    switch (mode) {
        case VisionMode::Mock:
            _driver = new MockVisionDriver();
            break;

        case VisionMode::I2C:
            _lastError = TrinovaError::NotInitialized;
            return false;

        case VisionMode::UART:
            _lastError = TrinovaError::NotInitialized;
            return false;
    }

    bool ok = _driver->begin();
    _lastError = ok ? TrinovaError::None : TrinovaError::NotInitialized;
    return ok;
}

VisionResult TrinovaVision::read() {
    VisionResult result{};

    if (!_driver) {
        result.connected = false;
        result.success = false;
        _lastError = TrinovaError::NotInitialized;
        return result;
    }

    bool ok = _driver->read(result);
    _totalReads++;

    if (!result.connected) {
        _lastError = TrinovaError::VisionNotConnected;
        _consecutiveErrors++;
    } else if (!ok) {
        _lastError = TrinovaError::VisionTimeout;
        _consecutiveErrors++;
    } else {
        _lastError = TrinovaError::None;
        _consecutiveErrors = 0;
        filterByConfidence(result);
    }

    if (_consecutiveErrors >= 5) {
        reset();
        _consecutiveErrors = 0;
    }

    return result;
}

bool TrinovaVision::isConnected() {
    if (!_driver) return false;
    return _driver->isConnected();
}

void TrinovaVision::setConfidence(uint8_t threshold) {
    if (threshold > 100) {
        _lastError = TrinovaError::InvalidConfidence;
        return;
    }
    _confidenceThreshold = threshold;
}

TrinovaError TrinovaVision::lastError() {
    return _lastError;
}

bool TrinovaVision::reset() {
    if (!_driver) return false;
    return _driver->reset();
}

void TrinovaVision::filterByConfidence(VisionResult &result) {
    if (_confidenceThreshold == 0) return;

    uint8_t kept = 0;
    for (uint8_t i = 0; i < result.count; i++) {
        if (result.objects[i].confidence >= _confidenceThreshold) {
            if (kept != i) {
                result.objects[kept] = result.objects[i];
            }
            kept++;
        }
    }
    result.count = kept;
    result.detected = (kept > 0);
}
void TrinovaVision::setMockScenario(MockScenario scenario) {
    if (_mode == VisionMode::Mock && _driver) {
        static_cast<MockVisionDriver*>(_driver)->setScenario(scenario);
    }
} 