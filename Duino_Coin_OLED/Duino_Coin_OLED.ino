// https://github.com/adafruit/Adafruit_BusIO
// https://github.com/adafruit/Adafruit_SSD1306
// https://github.com/adafruit/Adafruit-GFX-Library
// https://github.com/bblanchon/ArduinoJson

#include <Wire.h>
#include <ArduinoJson.h> // V6!
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>


/*
 * CHANGE THIS SCREEN RESOLUTION FIT TO YOUR OLED DISPLAY
 */
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

/* 
 *  OLED I2C ADDRESS
 *  
 *  USE 0x3D IF SCREEN SIZE 128x64 PIXELS
 *  USE 0x3C IF SCREEN SIZE 128x32 PIXELS
 *  
 */
#define SCREEN_ADDRESS 0x3C

#if ESP8266
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h> 
#define OLED_RESET     D4
#endif

#if ESP32
#include <WiFi.h>
#include <HTTPClient.h>
#define OLED_RESET     4
#endif

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char *ssid = "YOUR_SSID"; // Change this to your WiFi SSID
const char *password = "YOUR_SSID_PASSWORD"; // Change this to your WiFi password
const String ducoUser = "YOUR_DUINO_USERNAME"; // Change this to your Duino-Coin username

const String ducoReportJsonUrl = "https://server.duinocoin.com/v2/users/" + ducoUser + "?limit=1";

const int run_in_ms = 5000;

float lastAverageHash = 0.0;
float lastTotalHash = 0.0;


void setup() {

    Serial.begin(115200);
    setupWifi();

    initDisplayOled();

}

void loop() {
    if (runEvery(run_in_ms)) {

        float totalHashrate = 0.0;
        float avgHashrate = 0.0;
        int total_miner = 0;

        String input = httpGetString(ducoReportJsonUrl);
        DynamicJsonDocument doc (8000);
        DeserializationError error = deserializeJson(doc, input);

        if (error) {
            Serial.print("deserializeJson() failed: ");
            Serial.println(error.c_str());
            return;
        }

        JsonObject result = doc["result"];

        JsonObject result_balance = result["balance"];
        double result_balance_balance = result_balance["balance"];
        const char *result_balance_created = result_balance["created"];
        const char *result_balance_username = result_balance["username"];
        const char *result_balance_verified = result_balance["verified"];

        for (JsonObject result_miner : result["miners"].as<JsonArray>()) {
            float result_miner_hashrate = result_miner["hashrate"];
            totalHashrate = totalHashrate + result_miner_hashrate;
            total_miner++;
        }
        avgHashrate = totalHashrate / long(total_miner);
        long run_span = run_in_ms / 1000;


/*
 * BEGIN DISPLAY
 * 
 * refreshed every 5000 ms as in 'run_in_ms' variable
 *
 * I STRONGLY RECOMMEND PUT REFRESH RATE ABOVE 5000 MS,
 * IT WILL LIGHTEN CURRENT DUINO SERVER AND YOUR BOARD MEMORY BUFFER, REALLY.
 *
 */

        Serial.println("result_balance_username : " + String(result_balance_username));
        Serial.println("result_balance_balance : " + String(result_balance_balance));
        Serial.println("totalHashrate : " + String(totalHashrate));
        Serial.println("avgHashrate H/s : " + String(avgHashrate));
        Serial.println("total_miner : " + String(total_miner));

        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        display.println("User : " + String(result_balance_username));
        display.println("Total Miner : " + String(total_miner));
        display.println("Balance : " + String(result_balance_balance));
        display.println("KH/s (" + String(run_span) + "s): " + String(totalHashrate/1000));
        display.display();
    }

    /*
     * END DISPLAY
     */

}
