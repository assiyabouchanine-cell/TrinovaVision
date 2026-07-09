#include <Arduino.h>
#include "TrinovaVision.h"

TrinovaVision vision;

void setup() {
  Serial.begin(115200);
  delay(1000);

  vision.begin(VisionMode::Mock);
  vision.setConfidence(80);

  Serial.println("TrinovaVision - Mode Mock pret.");
}

void loop() {
  VisionResult result = vision.read();

  if (!result.connected) {
    Serial.println("Grove non connecte");
    delay(500);
    return;
  }

  if (result.detected) {
    Serial.print("Objet detecte: ");
    Serial.print(result.objects[0].label);
    Serial.print(" (");
    Serial.print(result.objects[0].confidence);
    Serial.println("%)");
  } else {
    Serial.println("Aucune detection");
  }

  delay(1000);
}