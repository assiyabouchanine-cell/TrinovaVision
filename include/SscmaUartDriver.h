#pragma once
#include "IVisionDriver.h"
#include "VisionResultConverter.h"
#include <Seeed_Arduino_SSCMA.h>

class SscmaUartDriver : public IVisionDriver {
public:
    SscmaUartDriver();

    bool begin() override;
    bool read(VisionResult &result) override;
    bool isConnected() override;
    bool reset() override;

private:
    SSCMA _ai;
    bool _ready;
};