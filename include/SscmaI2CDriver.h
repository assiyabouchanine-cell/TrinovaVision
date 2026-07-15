#pragma once
#include "IVisionDriver.h"
#include <Seeed_Arduino_SSCMA.h>

class SscmaI2CDriver : public IVisionDriver {
public:
    SscmaI2CDriver();

    bool begin() override;
    bool read(VisionResult &result) override;
    bool isConnected() override;
    bool reset() override;

private:
    SSCMA _ai;
    bool _ready;

    void convertToVisionResult(VisionResult &result);
};