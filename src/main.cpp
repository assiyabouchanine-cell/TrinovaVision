#include <Arduino.h>
#include <TrinovaVision.h>

TrinovaVision vision;

void setup() {
    Serial.begin(115200);
    delay(1000);

    vision.begin(VisionMode::Mock);
    vision.setConfidence(80);
}

void loop() {
    VisionResult result = vision.read();

    if (!result.connected) {
        Serial.println("Grove non connecté");
        delay(500);
        return;
    }

    if (result.detected) {
        Serial.print("Objet détecté : ");
        Serial.print(result.objects[0].label);
        Serial.print(" | confiance : ");
        Serial.println(result.objects[0].confidence);
    } else {
        Serial.println("Aucune détection");
    }

    delay(1000);
}