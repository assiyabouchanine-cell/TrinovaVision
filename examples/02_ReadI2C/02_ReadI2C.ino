#include <TrinovaVision.h>

TrinovaVision vision;

void setup() {
  Serial.begin(115200);
  delay(1000);

  bool ok = vision.begin(VisionMode::I2C);

  if (!ok) {
    Serial.println("Echec de connexion au module Grove Vision AI V2 (I2C)");
    return;
  }

  vision.setConfidence(70);
  Serial.println("TrinovaVision - Mode I2C pret.");
}

void loop() {
  VisionResult result = vision.read();

  if (!result.connected) {
    Serial.println("Grove non connecte");
    delay(500);
    return;
  }

  if (!result.success) {
    Serial.println("Timeout ou erreur de lecture");
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

  delay(500);
}