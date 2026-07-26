#include <Arduino.h>

void setup() {
    Serial.begin(115200);

    delay(2000);

    Serial.println();
    Serial.println("======================");
    Serial.println("JOE DSP TEST");
    Serial.println("ESP32-S3 BOOT OK");
    Serial.println("======================");
}

void loop() {
    Serial.println("Running...");
    delay(1000);
}
