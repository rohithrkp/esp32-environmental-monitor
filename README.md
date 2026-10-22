# ESP32 Environmental Monitoring System

An ESP32-based environmental monitoring system that reads temperature, humidity, and light levels, displaying the data on an OLED screen and providing visual/audible alerts based on configured thresholds.

## Features

- **Temperature & Humidity Monitoring**: Uses DHT22 sensor for accurate readings
- **OLED Display**: Shows real-time sensor data on a 128x64 SSD1306 display
- **Light Level Detection**: LDR sensor for ambient light monitoring
- **Visual Alerts**: LED changes color based on temperature state
  - **GREEN (Normal)**: Temperature < 22°C
  - **YELLOW (Warning)**: 22°C ≤ Temperature ≤ 24°C
  - **RED (Critical)**: Temperature > 24°C
- **Audible Alert**: Buzzer sounds when temperature is critical and alarm is enabled
- **Manual Override**: Button to toggle alarm on/off

## Hardware Requirements

| Component | Pin |
|-----------|-----|
| DHT22 | GPIO 4 |
| OLED (VCC) | 3.3V |
| OLED (GND) | GND |
| OLED (SCL) | GPIO 22 |
| OLED (SDA) | GPIO 21 |
| LDR | GPIO 34 |
| Button | GPIO 25 |
| LED (via transistor) | GPIO 14 |
| Buzzer | GPIO 27 |

## Libraries

- `DHT` - For DHT22 sensor
- `Wire` - For I2C communication
- `Adafruit_GFX` - Graphics library for OLED
- `Adafruit_SSD1306` - OLED display driver

Install these via Arduino IDE Library Manager.

## Usage

1. Connect the hardware as per the pin configuration above
2. Install required libraries
3. Upload the code to your ESP32
4. Open Serial Monitor (115200 baud) to view debug output
5. Press the button to toggle the alarm on/off
6. The buzzer will sound only when alarm is enabled AND temperature is critical (>24°C)

## License

MIT
