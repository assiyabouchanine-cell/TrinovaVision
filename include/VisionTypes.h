#pragma once
#include <stdint.h>

constexpr uint8_t TRINOVA_MAX_OBJECTS = 10;

enum class VisionMode {
    I2C,
    UART,
    Mock
};

enum class TrinovaError {
    None,
    NotInitialized,
    VisionNotConnected,
    VisionTimeout,
    InvalidConfidence,
    Unknown
};

struct VisionObject {
    int16_t classId;
    char    label[24];
    uint8_t confidence;
    int16_t x;
    int16_t y;
    int16_t width;
    int16_t height;
};

struct VisionResult {
    bool        connected;
    bool        success;
    bool        detected;
    uint8_t     count;
    VisionObject objects[TRINOVA_MAX_OBJECTS];
    uint32_t    preprocessMs;
    uint32_t    inferenceMs;
    uint32_t    postprocessMs;
};