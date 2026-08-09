#include "TrinovaVision.h"
TrinovaVision vision;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Utilise le mode Mock avec le scenario "plusieurs objets"
  // pour demontrer l'affichage sans avoir besoin du module physique.
  vision.begin(VisionMode::Mock);
  vision.setMockScenario(MockScenario::MultipleObjects);
  vision.setConfidence(0);

  Serial.println("TrinovaVision - Affichage de tous les objets detectes");
}

void loop() {
  VisionResult result = vision.read();

  if (!result.connected) {
    Serial.println("Grove non connecte");
    delay(500);
    return;
  }

  if (!result.detected) {
    Serial.println("Aucune detection");
    delay(1000);
    return;
  }

  Serial.print(result.count);
  Serial.println(" objet(s) detecte(s) :");

  for (uint8_t i = 0; i < result.count; i++) {
    Serial.print("  [");
    Serial.print(i);
    Serial.print("] ");
    Serial.print(result.objects[i].label);
    Serial.print(" - confiance: ");
    Serial.print(result.objects[i].confidence);
    Serial.print("% - position: (");
    Serial.print(result.objects[i].x);
    Serial.print(", ");
    Serial.print(result.objects[i].y);
    Serial.println(")");
  }

  Serial.println("---");
  delay(2000);
}