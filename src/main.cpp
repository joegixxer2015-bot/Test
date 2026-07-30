#include <Arduino.h>
#include <WiFi.h>
#include "AudioTools.h"

// กำหนดขา I2S ตามที่คุณต่อไว้จริง
#define I2S_BCK_PIN   15
#define I2S_LRCK_PIN  16
#define I2S_DATA1_PIN 17 // PCM5102A ตัวที่ 1
#define I2S_DATA2_PIN 18 // PCM5102A ตัวที่ 2

// ตั้งค่า I2S Output
I2SStream i2s; 
URLStream url;
StreamCopy copier(i2s, url); 

// ใส่ชื่อ Wi-Fi บ้าน/มือถือที่คุณเปิด Hotspot เพื่อให้ ESP32 ดึงเพลงได้
const char* ssid     = "iPhone";     // 👈 เปลี่ยนเป็นชื่อ Wi-Fi ของคุณ
const char* password = "12345678"; // 👈 เปลี่ยนเป็นรหัสผ่าน Wi-Fi

void setup() {
  Serial.begin(115200);
  delay(1000);

  // 1. เชื่อมต่อ Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  // 2. ตั้งค่าขา I2S Hardware
  auto config = i2s.defaultConfig(TX_MODE);
  config.pin_bck = I2S_BCK_PIN;
  config.pin_ws = I2S_LRCK_PIN;
  config.pin_data = I2S_DATA1_PIN; // ขาหลัก
  config.pin_data_rx = I2S_DATA2_PIN; // ขาสำรอง/แชนเนลขนาน
  config.sample_rate = 44100;
  config.bits_per_sample = 16;
  config.channels = 2;
  i2s.begin(config);

  // 3. เริ่มต้นรับ Audio Stream (ตัวอย่างเปิดสถานีวิทยุออนไลน์/Stream ตรงผ่าน IP)
  // หรือเปิด URL เพลง MP3 / Radio Stream ชัดระดับ HD
  url.begin("http://stream.zeno.fm/f3wvbbgah48uv", "audio/mp3");
  
  Serial.println("Audio Streaming Started! Playing Sound to PCM5102A...");
}

void loop() {
  // อ่านข้อมูลเพลงจาก Wi-Fi ยิงออก DAC PCM5102A ทั้ง 2 ตัวตลอดเวลา
  copier.copy();
}
