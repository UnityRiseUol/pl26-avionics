/*
 * File:        main.cpp
 * Author:      Joseph Wood
 * Last Update: 21/10/2025
 *
 * Project:   ELEC440 MEng Individual Project
 * Title:     "LASER - Rocket Flight Tracking and Control"
 */

// --- Includes ---
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"
#include "ICM_20948.h"
#include "Adafruit_BNO08x.h"
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#include "FS.h"
#include "SD_MMC.h"
#include <stdio.h>
#include <string.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

// --- Definitions ---
#define BMP_CS 18
#define ICM_CS 2
#define BNO08X_CS 4
#define BNO08X_INT 17
#define BNO08X_RESET 1

// LoRa Definitions
#define RFM95_CS    7
#define RFM95_RST   5
#define RFM95_INT   6
#define BAND 868E6

// --- WiFi & Web Server ---
auto ssid = "LIFTSv2";
auto password = "123456789";
WebServer server(80);

// --- Sensor Objects ---
Adafruit_BMP3XX bmp;
ICM_20948_SPI icm;
Adafruit_BNO08x bno08x(BNO08X_RESET);
sh2_SensorValue_t bno_sensorValue;
SFE_UBLOX_GNSS myGNSS;

// --- SD Card and File Handling ---
char logFileName[35];
File dataFile;

// --- SDIO Pin Definitions ---
int pin_sdioCLK = 38;
int pin_sdioCMD = 34;
int pin_sdioD0 = 39;
int pin_sdioD1 = 40;
int pin_sdioD2 = 47;
int pin_sdioD3 = 33;

// --- Global State Variables ---
volatile bool loggingEnabled = true;
constexpr int buttonPin = 15;

// --- Vertical Speed Calculation ---
#define VERTICAL_SPEED_SAMPLES 10
float altitude_samples[VERTICAL_SPEED_SAMPLES] = {0};
int sample_index = 0;
float last_altitude = 0;
unsigned long last_vs_time = 0;

// --- Configuration Struct ---
struct SystemConfig {
    float seaLevelPressureHPA;
};
SystemConfig config = {1013.25};

// --- Shared Data Structure (Full Resolution for SD Card) ---
struct AllSensorData {
    float bmp_temperature, bmp_pressure, bmp_altitude, bmp_vertical_speed;
    float icm_accX, icm_accY, icm_accZ;
    float icm_gyrX, icm_gyrY, icm_gyrZ;
    float icm_magX, icm_magY, icm_magZ;
    float bno_linearAccX, bno_linearAccY, bno_linearAccZ;
    float bno_gravityX, bno_gravityY, bno_gravityZ;
    float bno_quatR, bno_quatI, bno_quatJ, bno_quatK;
    float gps_latitude, gps_longitude, gps_altitude;
    float gps_speed, gps_heading;
    bool gps_valid;
};

// --- Telemetry Packet Structure (Compressed for LoRa) ---
// Total Size: 32 bytes
struct __attribute__((packed)) TelemetryPacket {
    float altitude;   // 4 bytes
    float v_speed;    // 4 bytes
    float lat;        // 4 bytes
    float lon;        // 4 bytes
    float qR;         // 4 bytes
    float qI;         // 4 bytes
    float qJ;         // 4 bytes
    float qK;         // 4 bytes
};

// Global instances
AllSensorData sensorData = {0};

// --- RTOS Synchronization ---
SemaphoreHandle_t xSensorDataMutex;
SemaphoreHandle_t xSpiMutex;

// --- Task Function Prototypes ---
void highFrequencySensorTask(void *pvParameters);
void gpsTask(void *pvParameters);
void loggingTask(void *pvParameters);
void buttonTask(void *pvParameters);
void webServerTask(void *pvParameters);
void loraTask(void *pvParameters);

// --- Configuration Functions ---
void saveConfiguration() {
    File configFile = SD_MMC.open("/config.txt", "w");
    if (configFile) {
        configFile.print("pressure=");
        configFile.println(config.seaLevelPressureHPA);
        configFile.close();
        Serial.println("Configuration saved to /config.txt");
    }
}

void loadConfiguration() {
    File configFile = SD_MMC.open("/config.txt", "r");
    if (!configFile) {
        Serial.println("config.txt not found. Creating default.");
        saveConfiguration();
    } else {
        while (configFile.available()) {
            String line = configFile.readStringUntil('\n');
            line.trim();
            if (line.startsWith("pressure=")) {
                config.seaLevelPressureHPA = line.substring(line.indexOf('=') + 1).toFloat();
            }
        }
        configFile.close();
        Serial.println("Configuration loaded.");
    }
}

// --- Web Server Handlers ---
void handleRoot() {
  File file = SD_MMC.open("/index.html", "r");
  if (!file) {
    server.send(500, "text/plain", "ERROR: index.html not found.");
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
}

void handleGetCsvList() {
  String json = "[";
  File root = SD_MMC.open("/");
  if (root) {
    File file = root.openNextFile();
    bool firstFile = true;
    while(file) {
      const char* fileName = file.name();
      if (strstr(fileName, ".csv")) {
        if (!firstFile) json += ",";
        json += "\"";
        if (fileName[0] == '/') json += (fileName + 1);
        else json += fileName;
        json += "\"";
        firstFile = false;
      }
      file.close();
      file = root.openNextFile();
    }
    root.close();
  }
  json += "]";
  server.send(200, "application/json", json);
}

void handleFileDownload() {
  if (server.hasArg("file")) {
    const String fileName = server.arg("file");
    if (fileName.indexOf('/') != -1 || fileName.indexOf("..") != -1) {
      server.send(400, "text/plain", "Invalid filename.");
      return;
    }
    String path = "/" + fileName;
    File file = SD_MMC.open(path, "r");
    if (!file) {
      server.send(404, "text/plain", "File not found.");
      return;
    }
    server.sendHeader("Content-Disposition", "attachment; filename=" + fileName);
    server.streamFile(file, "text/csv");
    file.close();
  } else {
    server.send(400, "text/plain", "Bad Request: 'file' missing.");
  }
}

void handleGetConfig() {
    JsonDocument doc;
    doc["pressure"] = String(config.seaLevelPressureHPA, 2);
    String output;
    serializeJson(doc, output);
    server.send(200, "application/json", output);
}

void handleUpdateConfig() {
    JsonDocument doc;
    const DeserializationError error = deserializeJson(doc, server.arg("plain"));
    if (error) {
        server.send(400, "text/plain", "Invalid JSON.");
        return;
    }
    if (doc["pressure"].is<float>()) {
        float newPressure = doc["pressure"];
        if (newPressure >= 800.0 && newPressure <= 1200.0) {
            config.seaLevelPressureHPA = newPressure;
            saveConfiguration();
            server.send(200, "text/plain", "Config updated.");
        } else {
            server.send(400, "text/plain", "Invalid pressure.");
        }
    }
}

void handleNotFound() {
  server.send(404, "text/plain", "Not Found");
}

// --- SETUP ---
void setup() {
    Serial.begin(115200);
    pinMode(buttonPin, INPUT);

    // Init SD Card
    if (!SD_MMC.setPins(pin_sdioCLK, pin_sdioCMD, pin_sdioD0, pin_sdioD1, pin_sdioD2, pin_sdioD3)) {
        Serial.println("SDIO pin error"); while(true);
    }
    if (!SD_MMC.begin()) {
        Serial.println("Card Mount Failed"); while(true);
    }

    loadConfiguration();

    // Log File Creation
    int maxLogNum = 0;
    File root = SD_MMC.open("/");
    if (root) {
        File file = root.openNextFile();
        while(file) {
            const char* fileName = file.name();
            if (strstr(fileName, "Flight_Data_") && strstr(fileName, ".csv")) {
                int currentNum = 0;
                if (sscanf(fileName, "/Flight_Data_%d.csv", &currentNum) == 1 || sscanf(fileName, "Flight_Data_%d.csv", &currentNum) == 1) {
                    if (currentNum > maxLogNum) { maxLogNum = currentNum; }
                }
            }
            file.close();
            file = root.openNextFile();
        }
        root.close();
    }
    int newLogNum = maxLogNum + 1;
    sprintf(logFileName, "/Flight_Data_%d.csv", newLogNum);

    dataFile = SD_MMC.open(logFileName, FILE_WRITE);
    if (dataFile) {
        dataFile.println("Time(ms),Temp(C),Pressure(hPa),Altitude(m),V_Speed(m/s),"
                         "ICM_AccX,ICM_AccY,ICM_AccZ,ICM_GyrX,ICM_GyrY,ICM_GyrZ,"
                         "ICM_MagX,ICM_MagY,ICM_MagZ,"
                         "BNO_LinAccX,BNO_LinAccY,BNO_LinAccZ,"
                         "BNO_GravX,BNO_GravY,BNO_GravZ,"
                         "BNO_QuatR,BNO_QuatI,BNO_QuatJ,BNO_QuatK,"
                         "GPS_Lat,GPS_Lon,GPS_Alt,GPS_Speed,GPS_Heading");
        dataFile.flush();
    }

    // Mutexes
    xSensorDataMutex = xSemaphoreCreateMutex();
    xSpiMutex = xSemaphoreCreateMutex();

    // Sensors
    Wire.begin();
    SPI.begin();

    if (!bmp.begin_SPI(BMP_CS)) { Serial.println("BMP Init Failed"); while (true); }
    icm.begin(ICM_CS, SPI);
    if (icm.status != ICM_20948_Stat_Ok) { Serial.println("ICM Init Failed"); while (true); }
    if (!bno08x.begin_SPI(BNO08X_CS, BNO08X_INT)) { Serial.println("BNO Init Failed"); while (true); }
    if (!myGNSS.begin()) { Serial.println("GNSS Init Failed"); while (true); }

    bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp.setOutputDataRate(BMP3_ODR_50_HZ);

    bno08x.enableReport(SH2_LINEAR_ACCELERATION, 5);
    bno08x.enableReport(SH2_GRAVITY, 10);
    bno08x.enableReport(SH2_GEOMAGNETIC_ROTATION_VECTOR, 10);
    myGNSS.setAutoPVT(true);

    Serial.println("Sensors Initialised.");

    // --- LoRa Setup (Optimized for Speed) ---
    LoRa.setSPI(SPI);
    LoRa.setPins(RFM95_CS, RFM95_RST, RFM95_INT);
    if (!LoRa.begin(BAND)) {
        Serial.println("LoRa Failed!");
    } else {
        LoRa.setTxPower(20);
        LoRa.setSignalBandwidth(500E3); // 500kHz for speed
        LoRa.setSpreadingFactor(7);     // SF7
        LoRa.setCodingRate4(5);         // CR 4/5
        Serial.println("LoRa High Speed (500kHz) Ready.");
    }

    // WiFi & Server
    WiFi.softAP(ssid, password);
    server.on("/", HTTP_GET, handleRoot);
    server.on("/list-csv", HTTP_GET, handleGetCsvList);
    server.on("/download", HTTP_GET, handleFileDownload);
    server.on("/getconfig", HTTP_GET, handleGetConfig);
    server.on("/updateconfig", HTTP_POST, handleUpdateConfig);
    server.onNotFound(handleNotFound);
    server.begin();
    Serial.println("Web Server Started.");

    // Tasks
    xTaskCreatePinnedToCore(highFrequencySensorTask, "SensTask", 4096, nullptr, 3, nullptr, 1);
    xTaskCreatePinnedToCore(gpsTask,                 "GPSTask",  4096, nullptr, 1, nullptr, 1);
    xTaskCreatePinnedToCore(loggingTask,             "LogTask",  4096, nullptr, 2, nullptr, 0);
    xTaskCreatePinnedToCore(buttonTask,              "BtnTask",  2048, nullptr, 2, nullptr, 0);
    xTaskCreatePinnedToCore(webServerTask,           "WebTask",  4096, nullptr, 1, nullptr, 0);
    xTaskCreatePinnedToCore(loraTask,                "LoRaTask", 4096, nullptr, 3, nullptr, 1); // Raised priority
}

// --- TASKS ---

void highFrequencySensorTask(void *pvParameters) {
    for (;;) {
        if (xSemaphoreTake(xSensorDataMutex, portMAX_DELAY) == pdTRUE) {

            if (xSemaphoreTake(xSpiMutex, portMAX_DELAY) == pdTRUE) {
                // BMP Reading
                if (bmp.performReading()) {
                    sensorData.bmp_temperature = bmp.temperature;
                    sensorData.bmp_pressure = bmp.pressure / 100.0;
                    sensorData.bmp_altitude = bmp.readAltitude(config.seaLevelPressureHPA);

                    const unsigned long current_time = millis();
                    if (last_vs_time > 0) {
                        const float dt = (current_time - last_vs_time) / 1000.0f;
                        if (dt > 0) {
                            const float raw_vs = (sensorData.bmp_altitude - last_altitude) / dt;
                            altitude_samples[sample_index] = raw_vs;
                            sample_index = (sample_index + 1) % VERTICAL_SPEED_SAMPLES;
                            float total_vs = 0;
                            for (int i = 0; i < VERTICAL_SPEED_SAMPLES; i++) {
                                total_vs += altitude_samples[i];
                            }
                            sensorData.bmp_vertical_speed = total_vs / VERTICAL_SPEED_SAMPLES;
                        }
                    }
                    last_altitude = sensorData.bmp_altitude;
                    last_vs_time = current_time;
                }

                // ICM Reading
                if(icm.dataReady()) {
                    constexpr float G_MPS2 = 9.80665;
                    icm.getAGMT();
                    sensorData.icm_accX = (icm.accX() / 1000.0) * G_MPS2;
                    sensorData.icm_accY = (icm.accY() / 1000.0) * G_MPS2;
                    sensorData.icm_accZ = (icm.accZ() / 1000.0) * G_MPS2;
                    sensorData.icm_gyrX = icm.gyrX();
                    sensorData.icm_gyrY = icm.gyrY();
                    sensorData.icm_gyrZ = icm.gyrZ();
                    sensorData.icm_magX = icm.magX();
                    sensorData.icm_magY = icm.magY();
                    sensorData.icm_magZ = icm.magZ();
                }

                // BNO Reading
                if (bno08x.getSensorEvent(&bno_sensorValue)) {
                    switch (bno_sensorValue.sensorId) {
                        case SH2_LINEAR_ACCELERATION:
                            sensorData.bno_linearAccX = bno_sensorValue.un.linearAcceleration.x;
                            sensorData.bno_linearAccY = bno_sensorValue.un.linearAcceleration.y;
                            sensorData.bno_linearAccZ = bno_sensorValue.un.linearAcceleration.z;
                            break;
                        case SH2_GRAVITY:
                            sensorData.bno_gravityX = bno_sensorValue.un.gravity.x;
                            sensorData.bno_gravityY = bno_sensorValue.un.gravity.y;
                            sensorData.bno_gravityZ = bno_sensorValue.un.gravity.z;
                            break;
                        case SH2_GEOMAGNETIC_ROTATION_VECTOR:
                            sensorData.bno_quatR = bno_sensorValue.un.geoMagRotationVector.real;
                            sensorData.bno_quatI = bno_sensorValue.un.geoMagRotationVector.i;
                            sensorData.bno_quatJ = bno_sensorValue.un.geoMagRotationVector.j;
                            sensorData.bno_quatK = bno_sensorValue.un.geoMagRotationVector.k;
                            break;
                        default: ;
                    }
                }
                xSemaphoreGive(xSpiMutex);
            }
            xSemaphoreGive(xSensorDataMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(2)); // Polling delay
    }
}

void gpsTask(void *pvParameters) {
    for (;;) {
        if (myGNSS.getPVT()) {
            if (xSemaphoreTake(xSensorDataMutex, portMAX_DELAY) == pdTRUE) {
                const long rawLat = myGNSS.getLatitude();
                const long rawLon = myGNSS.getLongitude();
                if (rawLat != 0 || rawLon != 0) {
                    sensorData.gps_latitude = rawLat / 10000000.0f;
                    sensorData.gps_longitude = rawLon / 10000000.0f;
                    sensorData.gps_altitude = myGNSS.getAltitude() / 1000.0f;
                    sensorData.gps_speed = myGNSS.getGroundSpeed() / 1000.0f;
                    sensorData.gps_heading = myGNSS.getHeading() / 100000.0f;
                    sensorData.gps_valid = true;
                }
                xSemaphoreGive(xSensorDataMutex);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void loggingTask(void *pvParameters) {
    unsigned long lastFlush = 0;
    for (;;) {
        if (loggingEnabled) {
            AllSensorData local;
            if (xSemaphoreTake(xSensorDataMutex, portMAX_DELAY) == pdTRUE) {
                memcpy(&local, &sensorData, sizeof(AllSensorData));
                xSemaphoreGive(xSensorDataMutex);
            }

            if (dataFile) {
                dataFile.print(millis());
                dataFile.print(","); dataFile.print(local.bmp_temperature, 2);
                dataFile.print(","); dataFile.print(local.bmp_pressure, 2);
                dataFile.print(","); dataFile.print(local.bmp_altitude, 2);
                dataFile.print(","); dataFile.print(local.bmp_vertical_speed, 2);
                dataFile.print(","); dataFile.print(local.icm_accX, 3);
                dataFile.print(","); dataFile.print(local.icm_accY, 3);
                dataFile.print(","); dataFile.print(local.icm_accZ, 3);
                dataFile.print(","); dataFile.print(local.icm_gyrX, 2);
                dataFile.print(","); dataFile.print(local.icm_gyrY, 2);
                dataFile.print(","); dataFile.print(local.icm_gyrZ, 2);
                dataFile.print(","); dataFile.print(local.icm_magX, 1);
                dataFile.print(","); dataFile.print(local.icm_magY, 1);
                dataFile.print(","); dataFile.print(local.icm_magZ, 1);
                dataFile.print(","); dataFile.print(local.bno_linearAccX, 3);
                dataFile.print(","); dataFile.print(local.bno_linearAccY, 3);
                dataFile.print(","); dataFile.print(local.bno_linearAccZ, 3);
                dataFile.print(","); dataFile.print(local.bno_gravityX, 3);
                dataFile.print(","); dataFile.print(local.bno_gravityY, 3);
                dataFile.print(","); dataFile.print(local.bno_gravityZ, 3);
                dataFile.print(","); dataFile.print(local.bno_quatR, 4);
                dataFile.print(","); dataFile.print(local.bno_quatI, 4);
                dataFile.print(","); dataFile.print(local.bno_quatJ, 4);
                dataFile.print(","); dataFile.print(local.bno_quatK, 4);
                dataFile.print(","); dataFile.print(local.gps_latitude, 6);
                dataFile.print(","); dataFile.print(local.gps_longitude, 6);
                dataFile.print(","); dataFile.print(local.gps_altitude, 2);
                dataFile.print(","); dataFile.print(local.gps_speed, 2);
                dataFile.print(","); dataFile.println(local.gps_heading, 2);
            }

            if (millis() - lastFlush >= 1000) {
                lastFlush = millis();
                if(dataFile) dataFile.flush();
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void buttonTask(void *pvParameters) {
    int lastState = LOW;
    unsigned long lastDebounce = 0;
    for (;;) {
        const int reading = digitalRead(buttonPin);
        if (reading != lastState) lastDebounce = millis();

        if ((millis() - lastDebounce) > 50) {
            if (reading == HIGH) {
                loggingEnabled = !loggingEnabled;
                if (loggingEnabled) {
                    Serial.println("Log Resumed");
                } else {
                    if(dataFile) {
                        dataFile.flush();
                    }
                    Serial.println("Log Stopped");
                }
                // Wait for release
                while(digitalRead(buttonPin) == HIGH) vTaskDelay(10);
            }
        }
        lastState = reading;
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

void webServerTask(void *pvParameters) {
    for (;;) {
        server.handleClient();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void loraTask(void *pvParameters) {
    vTaskDelay(pdMS_TO_TICKS(2000)); // Wait for system stability

    for (;;) {
        TelemetryPacket packet;

        // 1. Gather Data (Quick Mutex Lock)
        if (xSemaphoreTake(xSensorDataMutex, portMAX_DELAY) == pdTRUE) {
            packet.altitude = sensorData.bmp_altitude;
            packet.v_speed  = sensorData.bmp_vertical_speed;
            packet.lat      = sensorData.gps_latitude;
            packet.lon      = sensorData.gps_longitude;
            packet.qR       = sensorData.bno_quatR;
            packet.qI       = sensorData.bno_quatI;
            packet.qJ       = sensorData.bno_quatJ;
            packet.qK       = sensorData.bno_quatK;
            xSemaphoreGive(xSensorDataMutex);
        }

        // 2. Transmit Binary (SPI Mutex Lock)
        if (xSemaphoreTake(xSpiMutex, portMAX_DELAY) == pdTRUE) {
            LoRa.beginPacket();
            LoRa.write(reinterpret_cast<uint8_t *>(&packet), sizeof(packet));
            LoRa.endPacket(true);
            xSemaphoreGive(xSpiMutex);
        }

        // 3. Timing Control for 50Hz
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

void loop() {
    // Empty
}