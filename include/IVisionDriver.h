#pragma once
#include "VisionTypes.h"

class IVisionDriver {
public:
    virtual ~IVisionDriver() {}
    virtual bool begin() = 0;
    virtual bool read(VisionResult &result) = 0;
    virtual bool isConnected() = 0;
    virtual bool reset() = 0;
};