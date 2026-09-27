#include <DHT.h>
#include <avr/pgmspace.h>

// ============================================================
// SMART CROP MONITORING SYSTEM
// Arduino Uno
// ============================================================


// ============================================================
// PIN DEFINITIONS
// ============================================================

#define SOIL_MOISTURE_PIN A0
#define LIGHT_PIN A1
#define PH_PIN A2

#define DHT_PIN 2
#define DHT_TYPE DHT22

#define PUMP_LED_PIN 6
#define RELAY_PIN 7
#define RED_LED_PIN 8
#define GREEN_LED_PIN 9
#define BUZZER_PIN 10

DHT dht(DHT_PIN, DHT_TYPE);


// ============================================================
// CROP STRUCTURE
// ============================================================

struct Crop {

  char name[14];
  char category[13];

  float minPH;
  float maxPH;

  byte moisture;

  byte minTemp;
  byte maxTemp;

  byte minHumidity;
  byte maxHumidity;

  unsigned int minLight;
  unsigned int maxLight;
};


// ============================================================
// CROP DATABASE
// ============================================================

const Crop crops[] PROGMEM = {

  // STAPLE CROPS

  {
    "Wheat", "Staple Crop",
    6.0, 7.5, 35,
    15, 25,
    40, 70,
    300, 800
  },

  {
    "Rice", "Staple Crop",
    5.5, 7.0, 50,
    20, 35,
    60, 90,
    500, 1000
  },

  {
    "Maize", "Staple Crop",
    5.8, 7.0, 40,
    18, 30,
    50, 80,
    400, 900
  },

  {
    "Barley", "Staple Crop",
    6.0, 7.5, 35,
    12, 25,
    40, 70,
    300, 800
  },

  {
    "Sorghum", "Staple Crop",
    5.5, 7.5, 35,
    20, 32,
    40, 70,
    400, 900
  },

  {
    "Pearl Millet", "Staple Crop",
    5.5, 7.5, 30,
    22, 35,
    40, 70,
    400, 900
  },


  // PULSES

  {
    "Chickpea", "Pulse",
    6.0, 8.0, 30,
    15, 30,
    40, 70,
    300, 800
  },

  {
    "Lentil", "Pulse",
    6.0, 7.5, 30,
    15, 25,
    40, 70,
    300, 800
  },

  {
    "Pea", "Pulse",
    6.0, 7.5, 40,
    12, 24,
    50, 80,
    300, 700
  },


  // OILSEEDS

  {
    "Soybean", "Oilseed",
    6.0, 7.0, 40,
    20, 30,
    50, 80,
    400, 900
  },

  {
    "Groundnut", "Oilseed",
    6.0, 7.5, 35,
    22, 30,
    45, 75,
    400, 900
  },

  {
    "Mustard", "Oilseed",
    6.0, 7.5, 30,
    10, 25,
    40, 70,
    300, 800
  },


  // VEGETABLES

  {
    "Tomato", "Vegetable",
    5.5, 7.0, 40,
    18, 30,
    50, 80,
    500, 1000
  },

  {
    "Potato", "Vegetable",
    5.0, 6.5, 45,
    15, 25,
    50, 80,
    300, 700
  },

  {
    "Onion", "Vegetable",
    6.0, 7.0, 35,
    13, 25,
    40, 70,
    400, 900
  },

  {
    "Cabbage", "Vegetable",
    6.0, 7.5, 45,
    15, 25,
    50, 80,
    300, 800
  },

  {
    "Cauliflower", "Vegetable",
    6.0, 7.5, 45,
    15, 25,
    50, 80,
    300, 800
  },

  {
    "Carrot", "Vegetable",
    6.0, 7.0, 40,
    15, 25,
    50, 80,
    300, 800
  },

  {
    "Cucumber", "Vegetable",
    6.0, 6.5, 50,
    20, 30,
    60, 85,
    500, 1000
  },

  {
    "Spinach", "Vegetable",
    6.0, 7.5, 45,
    15, 25,
    50, 80,
    300, 800
  },

  {
    "Okra", "Vegetable",
    6.0, 7.5, 40,
    22, 32,
    50, 80,
    500, 1000
  },

  {
    "Brinjal", "Vegetable",
    5.5, 6.8, 40,
    22, 30,
    50, 80,
    500, 1000
  },

  {
    "Chilli", "Vegetable",
    5.5, 7.0, 40,
    20, 30,
    50, 80,
    400, 900
  },

  {
    "Beans", "Vegetable",
    6.0, 7.0, 45,
    18, 28,
    50, 80,
    400, 900
  },


  // FRUITS

  {
    "Mango", "Fruit",
    5.5, 7.5, 35,
    24, 35,
    50, 80,
    500, 1000
  },

  {
    "Banana", "Fruit",
    5.5, 7.0, 55,
    20, 35,
    60, 90,
    500, 1000
  },

  {
    "Apple", "Fruit",
    5.5, 7.0, 40,
    15, 25,
    40, 70,
    300, 800
  },

  {
    "Orange", "Fruit",
    5.5, 7.5, 40,
    18, 30,
    50, 80,
    500, 1000
  },

  {
    "Guava", "Fruit",
    5.0, 7.5, 40,
    20, 30,
    50, 80,
    500, 1000
  },

  {
    "Papaya", "Fruit",
    6.0, 7.0, 45,
    22, 32,
    60, 85,
    500, 1000
  },

  {
    "Watermelon", "Fruit",
    5.5, 7.0, 45,
    21, 32,
    50, 80,
    500, 1000
  },

  {
    "Strawberry", "Fruit",
    5.5, 6.5, 45,
    15, 25,
    50, 80,
    300, 700
  },

  {
    "Grapes", "Fruit",
    5.5, 7.0, 40,
    18, 30,
    50, 75,
    400, 900
  }
};


const byte cropCount = sizeof(crops) / sizeof(crops[0]);


// ============================================================
// CURRENT CROP
// ============================================================

Crop currentCrop;

byte selectedCrop = 0;


// ============================================================
// SENSOR VARIABLES
// IMPORTANT: THESE ARE NOT LEFT AT ZERO
// ============================================================

int soilMoisture = 50;

float soilPH = 6.5;

float lightLux = 500;

float temperature = 25;

float humidity = 60;


// ============================================================
// INPUT BUFFER
// ============================================================

char inputBuffer[30];

byte inputPosition = 0;

// Send dashboard data regularly while monitoring.
const unsigned long SENSOR_INTERVAL = 3000;
unsigned long lastSensorUpdate = 0;


// ============================================================
// LOAD CROP FROM PROGRAM MEMORY
// ============================================================

void loadCrop(byte index) {

  memcpy_P(
    &currentCrop,
    &crops[index],
    sizeof(Crop)
  );
}


// ============================================================
// CASE-INSENSITIVE NAME COMPARISON
// ============================================================

bool namesMatch(const char* a, const char* b) {

  while (*a && *b) {

    char ca = *a;
    char cb = *b;

    if (ca >= 'A' && ca <= 'Z') {
      ca = ca + 32;
    }

    if (cb >= 'A' && cb <= 'Z') {
      cb = cb + 32;
    }

    if (ca != cb) {
      return false;
    }

    a++;
    b++;
  }

  return (*a == '\0' && *b == '\0');
}


// ============================================================
// FIND CROP BY NAME
// ============================================================

int findCropByName(const char* input) {

  Crop temp;

  for (byte i = 0; i < cropCount; i++) {

    memcpy_P(
      &temp,
      &crops[i],
      sizeof(Crop)
    );

    if (namesMatch(input, temp.name)) {
      return i;
    }
  }

  return -1;
}


// ============================================================
// PRINT CROP MENU
// ============================================================

void printCropMenu() {

  Crop temp;

  Serial.println();
  Serial.println(F("========================================"));
  Serial.println(F("       SMART CROP MONITORING SYSTEM"));
  Serial.println(F("========================================"));

  Serial.println(F("Available Crops:"));
  Serial.println();

  for (byte i = 0; i < cropCount; i++) {

    memcpy_P(
      &temp,
      &crops[i],
      sizeof(Crop)
    );

    Serial.println(temp.name);
  }

  Serial.println();
  Serial.println(F("Type a crop name and press ENTER."));
  Serial.println(F("Example: Tomato"));
  Serial.println(F("========================================"));
}


// ============================================================
// SETUP
// ============================================================

void setup() {

  Serial.begin(9600);

  dht.begin();

  pinMode(PUMP_LED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(PUMP_LED_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);

  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);

  digitalWrite(BUZZER_PIN, LOW);

  loadCrop(0);

  delay(1000);

  Serial.println();
  Serial.println(F("========================================"));
  Serial.println(F("     SMART CROP MONITORING SYSTEM"));
  Serial.println(F("========================================"));

  printCropMenu();
}


// ============================================================
// MAIN LOOP
// ============================================================

void loop() {

  // ------------------------------------------------------------
  // Keep the original Serial crop-selection feature.
  // A dashboard/bridge can send: Rice\n
  // ------------------------------------------------------------

  while (Serial.available() > 0) {

    char incoming = Serial.read();

    if (incoming == '\r') {
      continue;
    }

    if (incoming == '\n') {

      inputBuffer[inputPosition] = '\0';

      if (inputPosition > 0) {

        int cropIndex = findCropByName(inputBuffer);

        if (cropIndex >= 0) {

          selectedCrop = cropIndex;
          loadCrop(selectedCrop);

          Serial.println();
          Serial.println(F("========================================"));
          Serial.print(F("SELECTED CROP: "));
          Serial.println(currentCrop.name);
          Serial.println(F("========================================"));

          showCropSpecifications();

          // Immediately send a fresh reading after crop selection.
          monitorCrop();

          lastSensorUpdate = millis();
        }

        else {

          Serial.println();
          Serial.println(F("Crop not found."));
          Serial.println(F("Please type a crop name exactly as shown."));
          printCropMenu();
        }
      }

      inputPosition = 0;
    }

    else {

      if (inputPosition < sizeof(inputBuffer) - 1) {
        inputBuffer[inputPosition] = incoming;
        inputPosition++;
      }
    }
  }

  // ------------------------------------------------------------
  // Periodic monitoring for the selected crop.
  // ------------------------------------------------------------

  unsigned long now = millis();

  if (now - lastSensorUpdate >= SENSOR_INTERVAL) {
    monitorCrop();
    lastSensorUpdate = now;
  }
}


// ============================================================
// SHOW CROP SPECIFICATIONS
// ============================================================

void showCropSpecifications() {

  Serial.println();

  Serial.println(F("----------------------------------------"));
  Serial.println(F("        CROP SPECIFICATIONS"));
  Serial.println(F("----------------------------------------"));

  Serial.print(F("Crop Name             : "));
  Serial.println(currentCrop.name);

  Serial.print(F("Category              : "));
  Serial.println(currentCrop.category);

  Serial.print(F("Required Soil pH      : "));
  Serial.print(currentCrop.minPH, 1);
  Serial.print(F(" - "));
  Serial.println(currentCrop.maxPH, 1);

  Serial.print(F("Minimum Soil Moisture : "));
  Serial.print(currentCrop.moisture);
  Serial.println(F("%"));

  Serial.print(F("Temperature Range     : "));
  Serial.print(currentCrop.minTemp);
  Serial.print(F(" - "));
  Serial.print(currentCrop.maxTemp);
  Serial.println(F(" C"));

  Serial.print(F("Humidity Range        : "));
  Serial.print(currentCrop.minHumidity);
  Serial.print(F(" - "));
  Serial.print(currentCrop.maxHumidity);
  Serial.println(F("%"));

  Serial.print(F("Light Range           : "));
  Serial.print(currentCrop.minLight);
  Serial.print(F(" - "));
  Serial.print(currentCrop.maxLight);
  Serial.println(F(" lux"));

  Serial.println(F("----------------------------------------"));
}


// ============================================================
// READ SOIL MOISTURE
// A0 = SOIL MOISTURE POTENTIOMETER
// ============================================================

int readSoilMoisture() {

  int rawValue = analogRead(SOIL_MOISTURE_PIN);

  int moisture =
    map(
      rawValue,
      0,
      1023,
      0,
      100
    );

  moisture =
    constrain(
      moisture,
      0,
      100
    );

  return moisture;
}


// ============================================================
// READ SOIL pH
// A2 = pH POTENTIOMETER
//
// Simulated range: 4.0 to 9.0
// ============================================================

float readPH() {

  int rawValue =
    analogRead(PH_PIN);

  float ph =
    4.0 +
    ((float)rawValue / 1023.0) * 5.0;

  return ph;
}


// ============================================================
// READ LIGHT
// A1 = LDR
//
// Simulated range: 0 to 1000 lux
// ============================================================

float readLight() {

  int rawValue =
    analogRead(LIGHT_PIN);

  float lux =
    ((float)rawValue / 1023.0) * 1000.0;

  return lux;
}


// ============================================================
// READ ALL LIVE SENSORS
// ============================================================

void readSensors() {

  // ----------------------------------------
  // SOIL MOISTURE
  // ----------------------------------------

  soilMoisture =
    readSoilMoisture();


  // ----------------------------------------
  // SOIL pH
  // ----------------------------------------

  soilPH =
    readPH();


  // ----------------------------------------
  // LIGHT
  // ----------------------------------------

  lightLux =
    readLight();


  // ----------------------------------------
  // DHT22 TEMPERATURE
  // ----------------------------------------

  float newTemperature =
    dht.readTemperature();


  // ----------------------------------------
  // DHT22 HUMIDITY
  // ----------------------------------------

  float newHumidity =
    dht.readHumidity();


  // ----------------------------------------
  // DHT22 SAFETY
  // ----------------------------------------
  // If DHT22 gives an invalid reading,
  // keep safe simulated values instead of 0.

  if (!isnan(newTemperature)) {

    temperature =
      newTemperature;
  }

  else {

    temperature = 25.0;
  }


  if (!isnan(newHumidity)) {

    humidity =
      newHumidity;
  }

  else {

    humidity = 60.0;
  }
}


// ============================================================
// SEND ONE JSON SENSOR PACKET TO THE DASHBOARD
// Human-readable Serial output is kept above/below this packet.
// The bridge/dashboard ignores all non-JSON lines.
// ============================================================

void sendDashboardJSON(bool warning) {

  bool pumpOn = soilMoisture < currentCrop.moisture;

  Serial.print(F("{\"crop\":\""));
  Serial.print(currentCrop.name);
  Serial.print(F("\",\"soilMoisture\":"));
  Serial.print(soilMoisture);
  Serial.print(F(",\"ph\":"));
  Serial.print(soilPH, 1);
  Serial.print(F(",\"temperature\":"));
  Serial.print(temperature, 1);
  Serial.print(F(",\"humidity\":"));
  Serial.print(humidity, 1);
  Serial.print(F(",\"light\":"));
  Serial.print(lightLux, 0);
  Serial.print(F(",\"pump\":"));
  Serial.print(pumpOn ? F("true") : F("false"));
  Serial.print(F(",\"relay\":"));
  Serial.print(pumpOn ? F("true") : F("false"));
  Serial.print(F(",\"status\":\""));
  Serial.print(warning ? F("WARNING") : F("OPTIMAL"));
  Serial.println(F("\"}"));
}


// ============================================================
// MONITOR SELECTED CROP
// ============================================================

void monitorCrop() {

  // Read the sensors NOW
  readSensors();


  Serial.println();

  Serial.println(F("========================================"));
  Serial.println(F("        LIVE SENSOR CONDITIONS"));
  Serial.println(F("========================================"));


  // ==========================================================
  // SOIL MOISTURE
  // ==========================================================

  Serial.print(F("Soil Moisture        : "));
  Serial.print(soilMoisture);
  Serial.println(F("%"));

  Serial.print(F("Required Minimum     : "));
  Serial.print(currentCrop.moisture);
  Serial.println(F("%"));


  // ==========================================================
  // SOIL pH
  // ==========================================================

  Serial.print(F("Soil pH              : "));
  Serial.println(soilPH, 2);

  Serial.print(F("Required pH          : "));
  Serial.print(currentCrop.minPH, 1);
  Serial.print(F(" - "));
  Serial.println(currentCrop.maxPH, 1);


  // ==========================================================
  // TEMPERATURE
  // ==========================================================

  Serial.print(F("Temperature          : "));
  Serial.print(temperature, 1);
  Serial.println(F(" C"));

  Serial.print(F("Required Temperature : "));
  Serial.print(currentCrop.minTemp);
  Serial.print(F(" - "));
  Serial.print(currentCrop.maxTemp);
  Serial.println(F(" C"));


  // ==========================================================
  // HUMIDITY
  // ==========================================================

  Serial.print(F("Humidity             : "));
  Serial.print(humidity, 1);
  Serial.println(F("%"));

  Serial.print(F("Required Humidity    : "));
  Serial.print(currentCrop.minHumidity);
  Serial.print(F(" - "));
  Serial.print(currentCrop.maxHumidity);
  Serial.println(F("%"));


  // ==========================================================
  // LIGHT
  // ==========================================================

  Serial.print(F("Light Intensity      : "));
  Serial.print(lightLux, 1);
  Serial.println(F(" lux"));

  Serial.print(F("Required Light       : "));
  Serial.print(currentCrop.minLight);
  Serial.print(F(" - "));
  Serial.print(currentCrop.maxLight);
  Serial.println(F(" lux"));


  Serial.println(F("----------------------------------------"));


  // ==========================================================
  // CHECK SOIL MOISTURE
  // ==========================================================

  bool soilDry =
    soilMoisture <
    currentCrop.moisture;


  // ==========================================================
  // CHECK pH
  // ==========================================================

  bool phLow =
    soilPH <
    currentCrop.minPH;

  bool phHigh =
    soilPH >
    currentCrop.maxPH;


  // ==========================================================
  // CHECK TEMPERATURE
  // ==========================================================

  bool temperatureLow =
    temperature <
    currentCrop.minTemp;

  bool temperatureHigh =
    temperature >
    currentCrop.maxTemp;

  bool temperatureBad =
    temperatureLow ||
    temperatureHigh;


  // ==========================================================
  // CHECK HUMIDITY
  // ==========================================================

  bool humidityLow =
    humidity <
    currentCrop.minHumidity;

  bool humidityHigh =
    humidity >
    currentCrop.maxHumidity;

  bool humidityBad =
    humidityLow ||
    humidityHigh;


  // ==========================================================
  // CHECK LIGHT
  // ==========================================================

  bool lightLow =
    lightLux <
    currentCrop.minLight;

  bool lightHigh =
    lightLux >
    currentCrop.maxLight;

  bool lightBad =
    lightLow ||
    lightHigh;


  // ==========================================================
  // WATER PUMP
  // ==========================================================

  if (soilDry) {

    digitalWrite(
      RELAY_PIN,
      HIGH
    );

    digitalWrite(
      PUMP_LED_PIN,
      HIGH
    );

    Serial.println(F("SOIL STATUS         : DRY"));
    Serial.println(F("IRRIGATION          : REQUIRED"));
    Serial.println(F("PUMP                : ON"));
  }

  else {

    digitalWrite(
      RELAY_PIN,
      LOW
    );

    digitalWrite(
      PUMP_LED_PIN,
      LOW
    );

    Serial.println(F("SOIL STATUS         : MOIST"));
    Serial.println(F("IRRIGATION          : NOT REQUIRED"));
    Serial.println(F("PUMP                : OFF"));
  }


  // ==========================================================
  // pH STATUS
  // ==========================================================

  if (phLow) {

    Serial.println(
      F("pH STATUS           : TOO ACIDIC")
    );
  }

  else if (phHigh) {

    Serial.println(
      F("pH STATUS           : TOO ALKALINE")
    );
  }

  else {

    Serial.println(
      F("pH STATUS           : NORMAL")
    );
  }


  // ==========================================================
  // TEMPERATURE STATUS
  // ==========================================================

  if (temperatureLow) {

    Serial.println(
      F("TEMPERATURE STATUS  : TOO LOW")
    );
  }

  else if (temperatureHigh) {

    Serial.println(
      F("TEMPERATURE STATUS  : TOO HIGH")
    );
  }

  else {

    Serial.println(
      F("TEMPERATURE STATUS  : NORMAL")
    );
  }


  // ==========================================================
  // HUMIDITY STATUS
  // ==========================================================

  if (humidityLow) {

    Serial.println(
      F("HUMIDITY STATUS     : TOO LOW")
    );
  }

  else if (humidityHigh) {

    Serial.println(
      F("HUMIDITY STATUS     : TOO HIGH")
    );
  }

  else {

    Serial.println(
      F("HUMIDITY STATUS     : NORMAL")
    );
  }


  // ==========================================================
  // LIGHT STATUS
  // ==========================================================

  if (lightLow) {

    Serial.println(
      F("LIGHT STATUS        : TOO LOW")
    );
  }

  else if (lightHigh) {

    Serial.println(
      F("LIGHT STATUS        : TOO HIGH")
    );
  }

  else {

    Serial.println(
      F("LIGHT STATUS        : NORMAL")
    );
  }


  // ==========================================================
  // OVERALL STATUS
  // ==========================================================

  bool warning =
    phLow ||
    phHigh ||
    temperatureBad ||
    humidityBad ||
    lightBad;


  Serial.println(F("----------------------------------------"));


  if (warning) {

    digitalWrite(
      RED_LED_PIN,
      HIGH
    );

    digitalWrite(
      GREEN_LED_PIN,
      LOW
    );

    tone(
      BUZZER_PIN,
      1000,
      250
    );

    Serial.println(
      F("OVERALL STATUS      : WARNING")
    );

    Serial.println(
      F("ACTION              : CHECK CONDITIONS")
    );
  }

  else {

    digitalWrite(
      RED_LED_PIN,
      LOW
    );

    digitalWrite(
      GREEN_LED_PIN,
      HIGH
    );

    noTone(BUZZER_PIN);

    Serial.println(
      F("OVERALL STATUS      : NORMAL")
    );

    Serial.println(
      F("ACTION              : CONDITIONS OK")
    );
  }


  // ==========================================================
  // PUMP SUMMARY
  // ==========================================================

  Serial.print(
    F("WATER PUMP          : ")
  );

  if (soilDry) {

    Serial.println(
      F("RUNNING")
    );
  }

  else {

    Serial.println(
      F("STOPPED")
    );
  }


  Serial.println(
    F("========================================")
  );

  // Machine-readable line for the dashboard/bridge.
  // This is intentionally one complete JSON object per line.
  sendDashboardJSON(warning);
}