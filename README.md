# Duino Coin Monitor OLED Display

# Install Library:
1. Install Library Arduino core for ESP8266 <br>
   `- https://github.com/esp8266/Arduino`
3. Install Library Arduino core for the ESP32 <br>
   `- https://github.com/espressif/arduino-esp32`
5. Install Library : <br>
`- https://github.com/adafruit/Adafruit_BusIO`<br>
`- https://github.com/adafruit/Adafruit_SSD1306`<br>
`- https://github.com/adafruit/Adafruit-GFX-Library`<br>
`- https://github.com/bblanchon/ArduinoJson`<br>

# OLED Display Software Setup:

1. OLED Display Screen Resolution, Change to your OLED display width and height.
```
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
```
2. OLED I2C ADDRESS
```
#define SCREEN_ADDRESS 0x3C
```
   - use <b>0x3D</b> if screen resolution 128x64 pixel
   - use <b>0x3C</b> if screen resolution 128x32 pixel
3. For ESP8266
   - According to lib spec https://github.com/adafruit/Adafruit_SSD1306, change pin OLED RESET

# Wiring:
|| ESP8266 | ESP32 | OLED |
|:-:| :----: | :----: | :-----: |
||3.3V | 3.3V | VCC |
||GND | GND | GND |
|`SCL`|D1 (GPIO5) | GPIO22| SCL |
|`SDA`|D2 (GPIO4) | GPIO21 | SDA |
