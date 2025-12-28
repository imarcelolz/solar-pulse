# SolarPulse

A compact, WiFi-enabled off-grid monitoring display built with ESP32-C3.

![SolarPulse](docs/solarpulse.png)

## Features

- 📊 Real-time OLED display (128x32) showing battery status, power consumption, and solar generation
- 💡 4 configurable LED indicators for alerts
- 📶 WiFi captive portal for easy network setup
- 🔌 Simple HTTP API for integration with any data source
- ⚡ Designed for 24/7 operation in off-grid systems

## Quick Start

```bash
# Clone and upload
git clone https://github.com/imarcelolz/solar-pulse.git
cd solar-pulse
pio run --target upload
```

1. Connect to the `SolarPulse` WiFi network
2. Configure your WiFi credentials at `http://192.168.4.1`
3. Send data via HTTP: `curl "http://<ip>/api?data=0000;Line1;Line2"`

## Documentation

For detailed architecture, protocol design, and setup instructions, see the **[full documentation](https://imarcelolz.github.io/projects/solar-monitor)**.

## License

MIT
