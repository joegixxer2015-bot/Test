#include <Arduino.h>
#include <WiFi.h>
#include "Audio.h"

#define I2S_BCK_PIN   15
#define I2S_LRCK_PIN  16
#define I2S_DATA1_PIN 17
#define I2S_DATA2_PIN 18


Audio audio;

const char* ssid     = "Iphone";     // 👈 ใส่ชื่อ Wi-Fi ของคุณ
const char* password = "12345678"; // 👈 ใส่รหัสผ่าน Wi-Fi

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // ตั้งค่า I2S Pin
  audio.setPinout(I2S_BCK_PIN, I2S_LRCK_PIN, I2S_DATA1_PIN, I2S_DATA2_PIN);
  audio.setVolume(12); // ปรับความดัง 0-21

  // ใส่ URL สตรีมเพลง/วิทยุออนไลน์
  audio.connecttohost("http://stream.zeno.fm/f3wvbbgah48uv");
}

void loop() {
  audio.loop();
}
