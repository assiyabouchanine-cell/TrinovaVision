# TrinovaVision

Bibliotheque C++ simplifiee pour piloter le **Grove Vision AI V2** (Himax WiseEye2 HX6538)
depuis un ESP32-S3, sans exposer les types ou l'API technique de **SSCMA**.

Projet realise dans le cadre du stage TrinovaTech - AI Robotics Core V1.

## Sommaire

- [Installation](#installation)
- [Cablage](#cablage)
- [Compilation](#compilation)
- [API](#api)
- [Exemples](#exemples)
- [Tests](#tests)
- [Limites connues](#limites-connues)
- [Depannage](#depannage)

## Installation

1. Cloner le depot :

git clone https://github.com/assiyabouchanine-cell/TrinovaVision.git

2. Ouvrir le dossier dans VS Code avec l'extension PlatformIO installee.
3. Les dependances (Seeed_Arduino_SSCMA, ArduinoJson) sont installees automatiquement
   au premier build, via `platformio.ini`.

## Cablage

Mode I2C (par defaut) :

| Grove Vision AI V2 | ESP32-S3 |
|---|---|
| VCC | 3V3 |
| GND | GND |
| SDA | SDA |
| SCL | SCL |

Mode UART (alternatif) : cf. `examples/04_ReadUART`.

## Compilation

pio run -e esp32-s3-devkitm-1


Pour flasher sur la carte :

pio run -e esp32-s3-devkitm-1 -t upload -t monitor


## API

```cpp
#include <TrinovaVision.h>

TrinovaVision vision;

vision.begin(VisionMode::Mock);   // ou VisionMode::I2C / VisionMode::UART
vision.setConfidence(80);          // seuil de confiance, 0-100

VisionResult result = vision.read();
if (result.detected) {
    Serial.println(result.objects[0].label);
}

vision.isConnected();
vision.lastError();
vision.reset();
vision.getStats();                 // statistiques (lectures totales, erreurs)
```

Voir `include/VisionTypes.h` pour le detail des structures `VisionObject` et `VisionResult`.

## Exemples

| Dossier | Description |
|---|---|
| `examples/01_ReadMock` | Lecture simple en mode simulation |
| `examples/02_ReadI2C` | Lecture reelle via I2C |
| `examples/03_AllObjects` | Affichage de plusieurs objets detectes |
| `examples/04_ReadUART` | Lecture reelle via UART |
| `examples/04_ValidationSemaine7` | Script de validation materielle complet |

## Tests

7 scenarios de simulation + 2 tests de robustesse, executables sans materiel :

pio test -e native


## Limites connues

- Le pilote UART n'a pas encore ete valide avec le module reel (optionnel selon le
  cahier des charges).
- Les labels des objets detectes via SSCMA sont generiques (`class_0`, `class_1`...)
  en l'absence d'une table de correspondance classe -> nom fournie par TrinovaTech.
- Maximum 10 objets detectes simultanement (`TRINOVA_MAX_OBJECTS`).

## Depannage

| Probleme | Solution |
|---|---|
| `pio` non reconnu dans le terminal | Utiliser le panneau PlatformIO (icone alien) ou le chemin complet vers `platformio.exe` |
| Echec de connexion I2C | Verifier le cablage SDA/SCL et l'alimentation 3V3 |
| Erreur de port lors de l'upload | Verifier le cable USB et le port COM detecte |