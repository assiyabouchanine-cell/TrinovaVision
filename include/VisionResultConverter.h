#pragma once
#include "VisionTypes.h"
#include <Seeed_Arduino_SSCMA.h>

class VisionResultConverter {
public:
    static void convert(SSCMA &ai, VisionResult &result);
};