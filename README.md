# Duino Coin Monitor OLED Display

# Install Library:
1. Install Library Arduino core for ESP8266
2. Install Library Arduino core for the ESP32
3. Install Library : <br>
`- https://github.com/adafruit/Adafruit_BusIO`<br>
`- https://github.com/adafruit/Adafruit_SSD1306`<br>
`- https://github.com/adafruit/Adafruit-GFX-Library`<br>
`- https://github.com/bblanchon/ArduinoJson`<br>


# Wiring:
|| ESP8266 | ESP32 | OLED |
|:-:| :----: | :----: | :-----: |
||3.3V | 3.3V | VCC |
||GND | GND | GND |
|`SCL`|D1 (GPIO5) | GPIO22| SCL |
|`SDA`|D2 (GPIO4) | GPIO21 | SDA |
