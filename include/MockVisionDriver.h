#pragma once
#include "IVisionDriver.h"

enum class MockScenario {
    PersonLeft,
    PersonCenter,
    NoDetection,
    MultipleObjects,
    LowConfidence,
    Disconnected,
    Timeout
};

class MockVisionDriver : public IVisionDriver {
public:
    MockVisionDriver();

    bool begin() override;
    bool read(VisionResult &result) override;
    bool isConnected() override;
    bool reset() override;

    void setScenario(MockScenario scenario);

private:
    bool _ready;
    MockScenario _scenario;

    void fillPersonLeft(VisionResult &r);
    void fillPersonCenter(VisionResult &r);
    void fillNoDetection(VisionResult &r);
    void fillMultipleObjects(VisionResult &r);
    void fillLowConfidence(VisionResult &r);
};  
