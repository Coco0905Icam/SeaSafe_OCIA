#include <bluefruit.h>

// Définir un UUID personnalisé pour le service et la caractéristique
#define SERVICE_UUID  0x1234  // UUID du service personnalisé
#define CHAR_UUID     0x5678  // UUID de la caractéristique personnalisée

// Crée un service BLE
BLEService customService(SERVICE_UUID);

// Crée une caractéristique BLE
BLECharacteristic customCharacteristic(CHAR_UUID);

// Valeur que l'on va envoyer (par exemple, un simple nombre)
uint8_t data = 100;

void setup() {
  // Initialiser la communication série
  Serial.begin(115200);

  // Démarrer le module BLE
  Bluefruit.begin();
  Bluefruit.setName("nRF52840_BLE");

  // Ajouter le service BLE
  customService.begin();

  // Ajouter la caractéristique à notre service BLE
  customCharacteristic.setProperties(CHR_PROPS_NOTIFY);
  customCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  customCharacteristic.setFixedLen(1);  // Taille de la donnée envoyée (1 octet)
  customCharacteristic.begin();
  
  // Démarrer la publicité BLE pour rendre le périphérique détectable
  Bluefruit.Advertising.addService(customService);
  Bluefruit.Advertising.start();
}

void loop() {
  // Vérifier si un appareil est connecté
  if (Bluefruit.connected()) {
    // Notifier la caractéristique avec la nouvelle valeur
    customCharacteristic.notify(&data, 1);
    Serial.println("Notification envoyée !");
  }

  delay(1000);  // Attendre 1 seconde avant d'envoyer à nouveau
}
