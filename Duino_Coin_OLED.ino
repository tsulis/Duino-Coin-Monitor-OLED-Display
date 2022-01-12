#include <ArduinoJson.h> //https://arduinojson.org
#include <Wire.h>
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

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#if ESP8266
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#endif

#if ESP32
#include <WiFi.h>
#include <HTTPClient.h>
#endif


const char* ssid     = "KARBELA20 2";
const char* password = "4gustu5#";
const String ducoUser = "fancyDuckling";

const String ducoReportJsonUrl = "https://server.duinocoin.com/v2/users/"+ducoUser+"?limit=1";


void setup() {

Serial.begin(115200);
setupWifi();

initDisplayOled();
//test_oled();

}

void loop() {

    float totalHashrate = 0.0;
    float avgHashrate = 0.0;
    double total_miner= 0;

    String input = httpGetString(ducoReportJsonUrl);

StaticJsonDocument<3000> doc;

DeserializationError error = deserializeJson(doc, input);

if (error) {
  Serial.print("deserializeJson() failed: ");
  Serial.println(error.c_str());
  return;
}

JsonObject result = doc["result"];

JsonObject result_balance = result["balance"];
double result_balance_balance = result_balance["balance"]; // 7256.5196157712135
const char* result_balance_created = result_balance["created"]; // "04/10/2021 12:42:26"
const char* result_balance_username = result_balance["username"]; // "fancyDuckling"
const char* result_balance_verified = result_balance["verified"]; // "no"
total_miner = result["miners"];

for (JsonObject result_miner : result["miners"].as<JsonArray>()) {


  float result_miner_hashrate = result_miner["hashrate"]; // 184.11, 193.83

totalHashrate = totalHashrate+result_miner_hashrate;

}

avgHashrate = totalHashrate / long(total_miner);

Serial.println("result_balance_username : "+String(result_balance_username));
Serial.println("result_balance_balance : "+String(result_balance_balance));
Serial.println("totalHashrate : "+String(totalHashrate));
Serial.println("avgHashrate : "+String(avgHashrate));

//  display.clearDisplay();
display.setTextSize(1); // Normal 1:1 pixel scale
display.setTextColor(WHITE); // Draw white text
display.setCursor(0,0); // Start at top-left corner
display.println("User : "+String(result_balance_username));
display.println("Total Miner "+String(total_miner));
display.println("Balance : "+String(result_balance_balance));
display.println("H/s : "+String(avgHashrate));
display.display();
    delay(5000);

}
