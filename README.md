# Smart Crop Monitoring System

Integrated Arduino Uno / Wokwi + web dashboard project.

## Working architecture

Dashboard → WebSocket `ws://127.0.0.1:8787` → `bridge.py` → RFC2217 `rfc2217://127.0.0.1:4000` → Wokwi Arduino

The dashboard sends the selected crop automatically. The Arduino keeps the existing crop database and Serial crop-selection logic, then sends periodic JSON sensor readings back through the bridge.

## Project files

- `Smart-Crop-Monitoring-Final.ino` — Arduino sketch
- `diagram.json` — Wokwi circuit
- `wokwi.toml` — Wokwi RFC2217 configuration
- `bridge.py` — bidirectional RFC2217 ↔ WebSocket bridge
- `requirements.txt` — Python packages
- `Smart-Crop-Dashboard-SENSOR.html` — local dashboard
- `index.html` — GitHub Pages-ready dashboard entry point
- `START-BRIDGE.bat` — starts the bridge
- `START-ALL.bat` — starts bridge + local web server and opens dashboard
- `PUBLIC-LINK-QR-SETUP.md` — public link and QR instructions

## Local live demo

1. Open this folder in VS Code.
2. Start the Wokwi simulation from the Wokwi Diagram Editor.
3. Make sure Wokwi is running with RFC2217 port `4000`.
4. Install packages once:
   `python -m pip install -r requirements.txt`
5. Run `START-ALL.bat`, or use two terminals:
   - `python bridge.py`
   - `python -m http.server 8080`
6. Open:
   `http://localhost:8080/Smart-Crop-Dashboard-SENSOR.html`
7. Select a crop in the dashboard. Do not type the crop into the Wokwi Serial Monitor.

## Expected live flow

Dashboard selects `Rice` → bridge sends `Rice\n` → Arduino changes to Rice → Arduino applies the existing Rice thresholds → Arduino emits sensor JSON → bridge forwards JSON → dashboard shows `● SENSOR DATA`.

## Sensor simulation

- A0: soil moisture potentiometer
- A1: LDR/light input
- A2: pH potentiometer
- D2: DHT22 temperature/humidity

A0 and A2 are simulated analog inputs rather than real agricultural sensors.

## Public dashboard

`index.html` is ready for static hosting such as GitHub Pages. A public static link can open the dashboard, but the current live sensor bridge remains local to the computer running Wokwi. See `PUBLIC-LINK-QR-SETUP.md` for the distinction and QR steps.

## Note about build files

The Arduino firmware build output is machine-generated. If Wokwi asks for a missing `build/*.hex` file on another computer, compile the sketch with Arduino CLI using the project's Arduino Uno board target before starting Wokwi.
