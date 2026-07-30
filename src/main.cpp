#include <Arduino.h>
#include <WiFi.h>
#include "AudioTools.h"
#include "AudioCodecs/CodecMP3Helix.h"

// กำหนดพิน I2S ตามที่คุณต่อจริง
#define I2S_BCK_PIN   15
#define I2S_LRCK_PIN  16
#define I2S_DATA1_PIN 17

// ตั้งค่า Wi-Fi
const char* ssid     = "iPhone";     // 👈 ใส่ชื่อ Wi-Fi ของคุณ
const char* password = "12345678"; // 👈 ใส่รหัสผ่าน Wi-Fi

// URL สถานีเพลงออนไลน์ (MP3 Stream)
const char* url = "http://stream.zeno.fm/f3wvbbgah48uv";

URLStream urlStream(ssid, password);
I2SStream i2s;
MP3DecoderHelix decoder;
EncodedAudioStream dec(&i2s, &decoder); // ตัวถอดรหัส MP3 ส่งเข้า I2S
StreamCopy copier(dec, urlStream);

void setup() {
  Serial.begin(115200);
  AudioToolsLogger.begin(Serial, AudioToolsLogLevel::Info);

  // 1. ตั้งค่า I2S Output
  auto config = i2s.defaultConfig(TX_MODE);
  config.pin_bck = I2S_BCK_PIN;
  config.pin_ws = I2S_LRCK_PIN;
  config.pin_data = I2S_DATA1_PIN;
  config.sample_rate = 44100;
  config.bits_per_sample = 16;
  config.channels = 2;
  i2s.begin(config);

  // 2. เริ่มทำงาน Stream เพลง
  dec.begin();
  urlStream.begin(url, "audio/mp3");
}

void loop() {
  // อ่านและเล่นเพลงต่อเนื่อง
  if (urlStream) {
    copier.copy();
  }
}
