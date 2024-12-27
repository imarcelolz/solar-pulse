# ESP32 Remote Display

This project allows you to set up an ESP32 device to display text information on an OLED display.

## Features

- Displays text information on an OLED display.
- Configures network credentials via a Wi-Fi hotspot.
- Simple API to update the display content.

## Getting Started

### Prerequisites

- ESP32 development board
- OLED display (compatible with Adafruit SSD1306 library)
- PlatformIO installed on your development environment

### Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/imarcelolz/esp32-remote-display.git
    cd esp32-remote-display
    ```

2. Open the project in your preferred IDE (e.g., Visual Studio Code with PlatformIO extension).

3. Connect your ESP32 board to your computer.

4. Upload the firmware to the ESP32:
    ```sh
    pio run --target upload
    ```

### Usage

1. When the device boots, it will create a Wi-Fi hotspot named `ESP32-Remote-Display`.

2. Connect to the Wi-Fi hotspot using your phone or computer.

3. Open a web browser and navigate to `http://192.168.4.1`. This will open the configuration portal.

4. Enter your network credentials (SSID and password) to connect the ESP32 to your Wi-Fi network.

5. Once connected, the device will display its IP address on the OLED display.

### API

You can update the display content using a simple HTTP GET request.

#### Endpoint

`GET /api?data=<code>;<first_line>;<second_line>`

#### Parameters

- `<code>`: A 4-digit code (e.g., `0000`).
- `<first_line>`: Text to display on the first line.
- `<second_line>`: Text to display on the second line.

#### Example

```sh
curl "http://<device_ip>/api?data=0000;Hello;World"
```