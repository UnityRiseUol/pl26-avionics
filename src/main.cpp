/*
 * File:        main.ino
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
// Note: Using default SPI pins for LoRa to share bus with sensors
// LORA_SCK_PIN 12, LORA_MISO_PIN 13, LORA_MOSI_PIN 11 are default on S3
#define BAND 868E6

// --- WiFi & Web Server ---
const char* ssid = "LIFTSv2";
const char* password = "123456789";
WebServer server(80);

// --- Sensor Objects ---
Adafruit_BMP3XX bmp;
ICM_20948_SPI icm;
Adafruit_BNO08x bno08x(BNO08X_RESET);
sh2_SensorValue_t bno_sensorValue;
SFE_UBLOX_GNSS myGNSS;

// --- SD Card and File Handling ---
char logFileName[35]; // Stores the generated log file name
File dataFile;        // File object for the log file

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

// --- NEW: Configuration Struct ---
// Holds all system settings. Add new settings here.
struct SystemConfig {
    float seaLevelPressureHPA;
};
// Initialize with default values. These are used if config.txt is missing.
SystemConfig config = {1013.25};

// --- Shared Data Structure ---
struct AllSensorData {
    float bmp_temperature, bmp_pressure, bmp_altitude;
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

// Global instance of the shared data structure, initialised to all zeros.
AllSensorData sensorData = {0};

// --- RTOS Synchronization ---
SemaphoreHandle_t xSensorDataMutex;
SemaphoreHandle_t xSpiMutex; // Mutex for shared SPI bus

// --- Task Function Prototypes ---
void highFrequencySensorTask(void *pvParameters);
void gpsTask(void *pvParameters);
void loggingTask(void *pvParameters);
void buttonTask(void *pvParameters);
void webServerTask(void *pvParameters);
void loraTask(void *pvParameters);

// --- Configuration Functions ---
// Saves the current configuration from the config struct to the SD card.
void saveConfiguration() {
    File configFile = SD_MMC.open("/config.txt", "w");
    if (configFile) {
        // Add a line for each setting in the SystemConfig struct
        configFile.print("pressure=");
        configFile.println(config.seaLevelPressureHPA);
        configFile.close();
        Serial.println("Configuration saved to /config.txt");
    } else {
        Serial.println("Error saving configuration!");
    }
}

// Loads configuration from the SD card into the config struct.
void loadConfiguration() {
    File configFile = SD_MMC.open("/config.txt", "r");
    if (!configFile) {
        Serial.println("config.txt not found. Creating with default values.");
        saveConfiguration(); // Create the file with default values
    } else {
        while (configFile.available()) {
            String line = configFile.readStringUntil('\n');
            line.trim();
            // Add an 'if' block for each setting
            if (line.startsWith("pressure=")) {
                config.seaLevelPressureHPA = line.substring(line.indexOf('=') + 1).toFloat();
            }
        }
        configFile.close();
        Serial.println("Configuration loaded from /config.txt");
    }
}


// --- Web Server Handlers ---
void handleRoot() {
  File file = SD_MMC.open("/index.html", "r");
  if (!file) {
    server.send(500, "text/plain", "ERROR: index.html not found on SD Card.");
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
        if (!firstFile) {
          json += ",";
        }
        json += "\"";
        if (fileName[0] == '/') {
            json += (fileName + 1);
        } else {
            json += fileName;
        }
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
    String fileName = server.arg("file");

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
    server.send(400, "text/plain", "Bad Request: 'file' parameter missing.");
  }
}

// --- Web handlers for configuration using JSON ---
// Sends the entire configuration struct as a JSON object.
void handleGetConfig() {
    JsonDocument doc;
    // Add each setting from the config struct to the JSON document
    doc["pressure"] = String(config.seaLevelPressureHPA, 2);

    String output;
    serializeJson(doc, output);
    server.send(200, "application/json", output);
}

// Receives a JSON object to update settings.
void handleUpdateConfig() {
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, server.arg("plain"));

    if (error) {
        server.send(400, "text/plain", "Invalid JSON body.");
        return;
    }

    bool configChanged = false;

    // Check for each setting in the received JSON
    if (doc["pressure"].is<float>()) {
        float newPressure = doc["pressure"];
        if (newPressure >= 800.0 && newPressure <= 1200.0) {
            config.seaLevelPressureHPA = newPressure;
            configChanged = true;
        } else {
            server.send(400, "text/plain", "Invalid pressure value provided.");
            return; // Stop processing on error
        }
    }

    // If any setting was successfully changed, save the entire config file.
    if (configChanged) {
        saveConfiguration();
        server.send(200, "text/plain", "Configuration updated successfully.");
    } else {
        server.send(200, "text/plain", "No valid configuration changes received.");
    }
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}


// --- SETUP: Runs once on boot ---
void setup() {
    //Begin serial comms
    Serial.begin(115200);

    pinMode(buttonPin, INPUT); // Set the button pin as an input

    // --- Initialise SD Card in SDIO mode ---
    if (!SD_MMC.setPins(pin_sdioCLK, pin_sdioCMD, pin_sdioD0, pin_sdioD1, pin_sdioD2, pin_sdioD3)) {
        Serial.println("SDIO pin assignment failed!"); while(true);
    }
    if (!SD_MMC.begin()) {
        Serial.println("Card Mount Failed"); while(true);
    }
    Serial.println("SD Card Initialised.");

    // --- Load configuration from SD Card ---
    loadConfiguration();

    // --- Create a new csv with incremental appended value ---
    int maxLogNum = 0;
    File root = SD_MMC.open("/");
    if (root) {
        File file = root.openNextFile();
        while(file) {
            const char* fileName = file.name();
            // Check if the file is a flight data log
            if (strstr(fileName, "Flight_Data_") && strstr(fileName, ".csv")) {
                int currentNum = 0;
                // Get the number from the filename
                if (sscanf(fileName, "/Flight_Data_%d.csv", &currentNum) == 1 || sscanf(fileName, "Flight_Data_%d.csv", &currentNum) == 1) {
                    if (currentNum > maxLogNum) { maxLogNum = currentNum; }
                }
            }
            file.close();
            file = root.openNextFile();
        }
        root.close();
    }

    int newLogNum = maxLogNum + 1; // Increment the appended number by 1
    sprintf(logFileName, "/Flight_Data_%d.csv", newLogNum); // Create new file name
    Serial.print("Opening log file for writing: "); Serial.println(logFileName);

    // Open the new file and write the CSV header
    dataFile = SD_MMC.open(logFileName, FILE_WRITE);
    if (dataFile) {
        dataFile.println("Time(ms),Temp(C),Pressure(hPa),Altitude(m),"
                         "ICM_AccX(m/s^2),ICM_AccY(m/s^2),ICM_AccZ(m/s^2),"
                         "ICM_GyrX(dps),ICM_GyrY(dps),ICM_GyrZ(dps),"
                         "ICM_MagX(uT),ICM_MagY(uT),ICM_MagZ(uT),"
                         "BNO_LinAccX(m/s^2),BNO_LinAccY(m/s^2),BNO_LinAccZ(m/s^2),"
                         "BNO_GravX(m/s^2),BNO_GravY(m/s^2),BNO_GravZ(m/s^2),"
                         "BNO_QuatR,BNO_QuatI,BNO_QuatJ,BNO_QuatK,"
                         "GPS_Lat,GPS_Lon,GPS_Alt(m),GPS_Speed(m/s),GPS_Heading(deg)");
        dataFile.flush(); // Ensure the header is written to the card immediately
    } else {
        Serial.println("Error creating log file!"); while(true);
    }

    // --- Create RTOS Mutexes ---
    xSensorDataMutex = xSemaphoreCreateMutex();
    xSpiMutex = xSemaphoreCreateMutex();

    // --- Initialise sensors ---
    Wire.begin(); // Starts I2C
    SPI.begin(); // Starts SPI (Default pins: SCK=12, MISO=13, MOSI=11 on S3)
    
    if (!bmp.begin_SPI(BMP_CS)) { Serial.println("BMP390 Init Failed"); while (true); }
    icm.begin(ICM_CS, SPI);
    if (icm.status != ICM_20948_Stat_Ok) { Serial.println("ICM20948 Init Failed"); while (true); }
    if (!bno08x.begin_SPI(BNO08X_CS, BNO08X_INT)) { Serial.println("BNO085 Init Failed"); while (true); }
    if (!myGNSS.begin()) { Serial.println(F("u-blox GNSS Init Failed")); while (true); }

    // Sensor settings
    bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp.setOutputDataRate(BMP3_ODR_50_HZ);

    bno08x.enableReport(SH2_LINEAR_ACCELERATION, 5);
    bno08x.enableReport(SH2_GRAVITY, 10);
    bno08x.enableReport(SH2_GEOMAGNETIC_ROTATION_VECTOR, 10);
    myGNSS.setAutoPVT(true);

    Serial.println("All sensors initialised.");

    // --- Initialise LoRa ---
    // Using the same SPI bus as sensors, so we configure it here
    LoRa.setSPI(SPI);
    LoRa.setPins(RFM95_CS, RFM95_RST, RFM95_INT);
    if (!LoRa.begin(BAND)) {
        Serial.println("Starting LoRa failed!");
        // We continue even if LoRa fails, but log it
    } else {
        LoRa.setTxPower(20);
        Serial.println("LoRa Initialized at 868MHz High Power!");
    }

    // --- Configure and start Web Server ---
    Serial.println("\nConfiguring Access Point...");
    if (!WiFi.softAP(ssid, password)) {
        Serial.println("Failed to start AP. Please reboot the device.");
        while (true) { delay(1000); }
    }
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    server.on("/", HTTP_GET, handleRoot);
    server.on("/list-csv", HTTP_GET, handleGetCsvList);
    server.on("/download", HTTP_GET, handleFileDownload);
    // --- MODIFIED: Use generic config routes ---
    server.on("/getconfig", HTTP_GET, handleGetConfig);
    server.on("/updateconfig", HTTP_POST, handleUpdateConfig);
    server.onNotFound(handleNotFound);
    server.begin();
    Serial.println("HTTP server started successfully.");

    // Create the concurrent tasks.
    // xTaskCreatePinnedToCore(function, name, stack size, params, priority, handle, core)
    xTaskCreatePinnedToCore(highFrequencySensorTask, "HighFreqTask", 4096, nullptr, 3, nullptr, 1); // Highest priority
    xTaskCreatePinnedToCore(gpsTask,                 "GPSTask",       4096, nullptr, 1, nullptr, 1); // Lowest priority
    xTaskCreatePinnedToCore(loggingTask,             "LoggingTask",   4096, nullptr, 2, nullptr, 0); // Medium priority, on core 0
    xTaskCreatePinnedToCore(buttonTask,              "ButtonTask",    2048, nullptr, 2, nullptr, 0); // Medium priority, on core 0
    xTaskCreatePinnedToCore(webServerTask,           "WebServerTask", 4096, nullptr, 1, nullptr, 0); // Low priority, on core 0
    xTaskCreatePinnedToCore(loraTask,                "LoRaTask",      4096, nullptr, 2, nullptr, 1); // Medium priority, on core 1
}

// --- TASK 1: High-Frequency Sensor Polling ---
// Priority: 3 (High).
// Purpose: Reads IMU and barometer sensors as fast as possible.
void highFrequencySensorTask(void *pvParameters) {
    for (;;) { // Infinite loop
        // Attempt to take the mutex, will wait indefinitely if busy
        if (xSemaphoreTake(xSensorDataMutex, portMAX_DELAY) == pdTRUE) {
            
            // Take SPI mutex before accessing sensors
            if (xSemaphoreTake(xSpiMutex, portMAX_DELAY) == pdTRUE) {
                // Read BMP390
                if (bmp.performReading()) {
                    sensorData.bmp_temperature = bmp.temperature;
                    sensorData.bmp_pressure = bmp.pressure / 100.0;
                    sensorData.bmp_altitude = bmp.readAltitude(config.seaLevelPressureHPA);
                }

                // Read ICM20948
                icm.getAGMT();
                constexpr float G_MPS2 = 9.80665;
                sensorData.icm_accX = (icm.accX() / 1000.0) * G_MPS2;
                sensorData.icm_accY = (icm.accY() / 1000.0) * G_MPS2;
                sensorData.icm_accZ = (icm.accZ() / 1000.0) * G_MPS2;
                sensorData.icm_gyrX = icm.gyrX();
                sensorData.icm_gyrY = icm.gyrY();
                sensorData.icm_gyrZ = icm.gyrZ();
                sensorData.icm_magX = icm.magX();
                sensorData.icm_magY = icm.magY();
                sensorData.icm_magZ = icm.magZ();

                // Read BNO085
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
                xSemaphoreGive(xSpiMutex); // Release SPI bus
            }
            // Release the data mutex lock
            xSemaphoreGive(xSensorDataMutex);
        }
        // Wait for 1 millisecond
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

// --- TASK 2: GPS Polling ---
// Priority: 1 (Low).
// Purpose: Checks for new data from the GPS module.
void gpsTask(void *pvParameters) {
    for (;;) { // Infinite loop
        // myGNSS.getPVT() is a blocking function whilst waiting for new data, RTOS will execute other tasks whilst waiting
        if (myGNSS.getPVT()) {
            // New message arrived
            if (xSemaphoreTake(xSensorDataMutex, portMAX_DELAY) == pdTRUE) {
                long rawLat = myGNSS.getLatitude();
                long rawLon = myGNSS.getLongitude();
                if (rawLat != 0 || rawLon != 0) { // Check for a valid fix
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
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}

// --- TASK 3: Data Logging ---
// Priority: 2 (Medium)
// Purpose: Writes current sensor data to SD card.
void loggingTask(void *pvParameters) {
    unsigned long lastFlush = 0;

    for (;;) { // Infinite loop
        if (loggingEnabled) {
            constexpr unsigned long flushInterval = 1000;
            AllSensorData localData; // Create a local copy of sensor data

            // Locks the mutex and makes a copy of the data, then immediately unlocks
            if (xSemaphoreTake(xSensorDataMutex, portMAX_DELAY) == pdTRUE) {
                memcpy(&localData, &sensorData, sizeof(AllSensorData));
                xSemaphoreGive(xSensorDataMutex);
            }

            // Writes to SD card using local copy without blocking access to the global struct.
            if (dataFile) {
                dataFile.print(millis());
                dataFile.print(","); dataFile.print(localData.bmp_temperature, 2);
                dataFile.print(","); dataFile.print(localData.bmp_pressure, 2);
                dataFile.print(","); dataFile.print(localData.bmp_altitude, 2);
                dataFile.print(","); dataFile.print(localData.icm_accX, 4);
                dataFile.print(","); dataFile.print(localData.icm_accY, 4);
                dataFile.print(","); dataFile.print(localData.icm_accZ, 4);
                dataFile.print(","); dataFile.print(localData.icm_gyrX, 4);
                dataFile.print(","); dataFile.print(localData.icm_gyrY, 4);
                dataFile.print(","); dataFile.print(localData.icm_gyrZ, 4);
                dataFile.print(","); dataFile.print(localData.icm_magX, 4);
                dataFile.print(","); dataFile.print(localData.icm_magY, 4);
                dataFile.print(","); dataFile.print(localData.icm_magZ, 4);
                dataFile.print(","); dataFile.print(localData.bno_linearAccX, 4);
                dataFile.print(","); dataFile.print(localData.bno_linearAccY, 4);
                dataFile.print(","); dataFile.print(localData.bno_linearAccZ, 4);
                dataFile.print(","); dataFile.print(localData.bno_gravityX, 4);
                dataFile.print(","); dataFile.print(localData.bno_gravityY, 4);
                dataFile.print(","); dataFile.print(localData.bno_gravityZ, 4);
                dataFile.print(","); dataFile.print(localData.bno_quatR, 4);
                dataFile.print(","); dataFile.print(localData.bno_quatI, 4);
                dataFile.print(","); dataFile.print(localData.bno_quatJ, 4);
                dataFile.print(","); dataFile.print(localData.bno_quatK, 4);
                dataFile.print(","); dataFile.print(localData.gps_latitude, 6);
                dataFile.print(","); dataFile.print(localData.gps_longitude, 6);
                dataFile.print(","); dataFile.print(localData.gps_altitude, 2);
                dataFile.print(","); dataFile.print(localData.gps_speed, 2);
                dataFile.print(","); dataFile.println(localData.gps_heading, 2);
            }

            // Flushes data at 1Hz so data isn't lost in case of power loss
            if (millis() - lastFlush >= flushInterval) {
                lastFlush = millis();
                if(dataFile) dataFile.flush();
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

// --- TASK 4: Button Handling ---
// Priority: 2 (Medium)
// Purpose: Manages the start/stop logging button
void buttonTask(void *pvParameters) {
    int debouncedState = LOW;  // The stable state of button
    int lastReading = LOW;     // The last reading from the pin
    unsigned long lastDebounceTime = 0;

    for (;;) {
        constexpr unsigned long debounceDelay = 50;
        // Infinite loop
        int currentReading = digitalRead(buttonPin);

        // If the switch changes state, reset the debounce timer.
        if (currentReading != lastReading) {
            lastDebounceTime = millis();
        }

        // Detect debounced button press
        if ((millis() - lastDebounceTime) > debounceDelay) {
            if (currentReading != debouncedState) {
                debouncedState = currentReading;

                // If button pressed
                if (debouncedState == HIGH) {
                    // Toggle logging state
                    loggingEnabled = !loggingEnabled;
                    if (loggingEnabled) {
                        // If logging is now on, re-open the file
                        dataFile = SD_MMC.open(logFileName, FILE_APPEND);
                        Serial.println("\nLogging resumed.");
                    } else {
                        // If logging is now off, flush and close the file
                        if(dataFile) {
                           dataFile.flush();
                           dataFile.close();
                        }
                        Serial.println("\nLogging stopped. File closed.");
                    }
                }
            }
        }

        // Update the last reading for the next loop iteration.
        lastReading = currentReading;
        // Check button state every 10ms.
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

// --- TASK 5: Web Server Handling ---
// Priority: 1 (Low).
// Purpose: Handles web server client requests
void webServerTask(void *pvParameters) {
  for (;;) {
    server.handleClient();
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

// --- TASK 6: LoRa Transmitter ---
// Purpose: Broadcasts sensor data every second via LoRa.
void loraTask(void *pvParameters) {
  Serial.println("ESP32-S3 LoRa Transmitter Task Started");

  // Offset start to avoid sync with logging flush
  vTaskDelay(pdMS_TO_TICKS(500));

  for (;;) { // Infinite loop
    float altitude = 0, latitude = 0, longitude = 0;

    // Safely read the sensor data
    if (xSemaphoreTake(xSensorDataMutex, portMAX_DELAY) == pdTRUE) {
        altitude = sensorData.bmp_altitude;
        latitude = sensorData.gps_latitude;
        longitude = sensorData.gps_longitude;
        xSemaphoreGive(xSensorDataMutex);
    }

    // Construct the message string
    char message[100];
    snprintf(message, sizeof(message), "ALT:%.2f,LAT:%.6f,LON:%.6f", altitude, latitude, longitude);

    Serial.print("Sending LoRa packet: ");
    Serial.println(message);

    // Take SPI mutex before using LoRa
    if (xSemaphoreTake(xSpiMutex, portMAX_DELAY) == pdTRUE) {
        LoRa.beginPacket();
        LoRa.print(message);
        LoRa.endPacket(true); // Async send to minimize blocking time
        xSemaphoreGive(xSpiMutex);
    }

    Serial.println("Packet sent.");

    vTaskDelay(pdMS_TO_TICKS(1000)); // Use FreeRTOS delay
  }
}

// --- Main Loop ---
void loop() {
    // Left empty as FreeRTOS handles task scheduling
}
