#include "VisionResultConverter.h"
#include <string.h>

void VisionResultConverter::convert(SSCMA &ai, VisionResult &result) {
    uint8_t n = ai.boxes().size();
    if (n > TRINOVA_MAX_OBJECTS) {
        n = TRINOVA_MAX_OBJECTS;
    }

    result.count = n;
    result.detected = (n > 0);

    for (uint8_t i = 0; i < n; i++) {
        result.objects[i].classId = ai.boxes()[i].target;
        result.objects[i].confidence = ai.boxes()[i].score;
        result.objects[i].x = ai.boxes()[i].x;
        result.objects[i].y = ai.boxes()[i].y;
        result.objects[i].width = ai.boxes()[i].w;
        result.objects[i].height = ai.boxes()[i].h;

        snprintf(result.objects[i].label, sizeof(result.objects[i].label),
                 "class_%d", result.objects[i].classId);
    }
}