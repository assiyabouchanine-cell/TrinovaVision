#pragma once
#include "VisionTypes.h"
#include "IVisionDriver.h"
#include "MockVisionDriver.h"

class TrinovaVision {
public:
    TrinovaVision();
    ~TrinovaVision();

    bool begin(VisionMode mode);
    VisionResult read();
    bool isConnected();
    void setConfidence(uint8_t threshold);
    TrinovaError lastError();
    bool reset();
    void setMockScenario(MockScenario scenario);

private:
    IVisionDriver* _driver;
    VisionMode     _mode;
    uint8_t        _confidenceThreshold;
    TrinovaError   _lastError;
    uint32_t       _totalReads;
    uint8_t        _consecutiveErrors;

    void filterByConfidence(VisionResult &result);
};