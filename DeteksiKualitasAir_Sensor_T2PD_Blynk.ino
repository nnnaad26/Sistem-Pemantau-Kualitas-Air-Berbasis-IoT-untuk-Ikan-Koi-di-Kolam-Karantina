// Aplikasi Blynk
#define BLYNK_TEMPLATE_ID "TMPL6Kr_qEKgs"
#define BLYNK_TEMPLATE_NAME "Sistem Pemantau Kualitas Air Ikan Koi"
#define BLYNK_AUTH_TOKEN "DinWSOS7m1lr7HT4OGOHjcllUXOg_DFK"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "nad";
// char ssid[] = "IndoMicro";
char pass[] = "12345678";

bool data = false;
String status = "";
WidgetLED led1(V8);

// Modul ADS1115 (Sensor PH, Sensor TDS & Sensor Turbidity)
#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <math.h>
Adafruit_ADS1115 ads;
float turbidity;
float tdsVoltage = 0.0, tds = 0.0, temperature = 25.0;
float calibration_value = 14.0;  // Nilai maksimal ph
float ph = 0;

// Sensor DS18b20
#include <OneWire.h>
#include <DallasTemperature.h>
#define SENSOR_PIN 5
OneWire oneWire(SENSOR_PIN);
DallasTemperature DS18B20(&oneWire);
float tempC;

// LCD OLED
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3c
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET -1     // QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Modul Relay
#define heater1 23
#define heater2 19

// LED & Buzzer
#define buzzer 16
#define led 17

// Variabel Tambahan
unsigned long previousMillis = 0;
const unsigned long interval = 100;
bool btHeater = false;
String keteranganSuhu = "",
       keteranganPH = "",
       keteranganTDS = "",
       keteranganTurbidity = "";
String feedbackSuhu = "",
       feedbackTDS = "",
       feedbackPH = "",
       feedbackTurbidity = "";

void setup() {
  setupHeater();
  Serial.begin(115200);
  Wire.begin();
  DS18B20.begin();
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);

  display.begin(i2c_Address, true);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);

  if (!ads.begin(0x48)) {
    Serial.println("Gagal mendeteksi ADS1115. Periksa koneksi!");
    while (1)
      beep();
  }

  showConnecting();
  Serial.println("Loading ...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  beepConnecting();
  delay(1000);
  display.clearDisplay();
}

void loop() {
  Blynk.run();
  bacaDataSensor();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    tampilNilaiSensor();
  }

  if (tempC < 20 || btHeater) {
    digitalWrite(heater1, 0);
    digitalWrite(heater2, 0);
    // led1.on();
    digitalWrite(led, 1);
  } else if (tempC >= 20 && !btHeater) {
    digitalWrite(heater1, 1);
    digitalWrite(heater2, 1);
    digitalWrite(led, 0);
    // led1.off();
  }

  if (data) {
    // Keterangan Status Kualitas Air
    if ((turbidity >= 0 && turbidity <= 30) && (tds >= 300 && tds <= 500) && (ph >= 6.5 && ph <= 8) && (tempC >= 20 && tempC <= 28)) {
      status = "Kualitas Air Normal";
      digitalWrite(buzzer, 0);  // Buzzer Mati
    } else if (turbidity > 30 || (tds < 300 || tds > 500) || (ph < 6.5 || ph > 8) || (tempC < 20 || tempC > 28)) {
      status = "Kualitas Air Tidak Normal";
      digitalWrite(buzzer, 1);  // Buzzer Aktif
    }
    // Keterangan Suhu
    if (tempC < 20) {
      keteranganSuhu = "Suhu Rendah";
      feedbackSuhu = "Aktifkan heater, suhu terlalu dingin";
    } else if (tempC >= 20 && tempC <= 28) {
      keteranganSuhu = "Suhu Normal";
      feedbackSuhu = "Suhu stabil dan ideal untuk koi";
    } else {
      keteranganSuhu = "Suhu Tinggi";
      feedbackSuhu = "Suhu tinggi, segera dinginkan air";
    }
    // Keterangan PH
    if (ph < 6.5) {
      keteranganPH = "PH Rendah";
      feedbackPH = "pH rendah, tambahkan kapur atau ganti air";
    } else if (ph >= 6.5 && ph <= 8) {
      keteranganPH = "PH Normal";
      feedbackPH = "pH stabil dan aman untuk koi";
    } else {
      keteranganPH = "PH Tinggi";
      feedbackPH = "pH tinggi, tambahkan penurun pH alami";
    }
    // Keterangan TDS
    if (tds >= 0 && tds <= 300) {
      keteranganTDS = "TDS Rendah";
      feedbackTDS = "TDS rendah, tambahkan mineral";
    } else if (tds >= 300 && tds <= 500) {
      keteranganTDS = "TDS Normal";
      feedbackTDS = "TDS ideal, air dalam kondisi baik";
    } else {
      keteranganTDS = "TDS Tinggi";
      feedbackTDS = "TDS tinggi, ganti air segera";
    }
    // Keterangan Turbidity
    if (turbidity >= 0 && turbidity <= 30) {
      keteranganTurbidity = "Air Jernih";
      feedbackTurbidity = "Air jernih, kondisi baik";
    } else if (turbidity >= 31 && turbidity <= 60) {
      keteranganTurbidity = "Air Keruh";
      feedbackTurbidity = "Air keruh, periksa filter dan dasar kolam";
    } else {
      keteranganTurbidity = "Air Kotor";
      feedbackTurbidity = "Air kotor, lakukan pergantian air";
    }

    Blynk.virtualWrite(V0, ph);
    Blynk.virtualWrite(V1, tempC);
    Blynk.virtualWrite(V2, tds);
    Blynk.virtualWrite(V3, turbidity);
    Blynk.virtualWrite(V5, status);

    Blynk.virtualWrite(V9, keteranganSuhu);
    Blynk.virtualWrite(V10, keteranganPH);
    Blynk.virtualWrite(V11, keteranganTDS);
    Blynk.virtualWrite(V12, keteranganTurbidity);

    Blynk.virtualWrite(V13, feedbackSuhu);
    Blynk.virtualWrite(V14, feedbackPH);
    Blynk.virtualWrite(V15, feedbackTDS);
    Blynk.virtualWrite(V16, feedbackTurbidity);
  } else {
    // Keterangan Status Kualitas Air
    if ((turbidity >= 0 && turbidity <= 30) && (tds >= 300 && tds <= 500) && (ph >= 6.5 && ph <= 8) && (tempC >= 20 && tempC <= 28)) {
      digitalWrite(buzzer, 0);  // Buzzer Mati
    } else if (turbidity > 30 || (tds < 300 || tds > 500) || (ph < 6.5 || ph > 8) || (tempC < 20 || tempC > 28)) {
      digitalWrite(buzzer, 1);  // Buzzer Aktif
    }
  }

  delay(10);
}

// Data Sensor
BLYNK_WRITE(V4) {
  data = param.asInt() == 1;
}
BLYNK_WRITE(V6) {
  if (param.asInt() == 1) {
    btHeater = true;
  }
}
BLYNK_WRITE(V7) {
  if (param.asInt() == 1) {
    btHeater = false;
  }
}
