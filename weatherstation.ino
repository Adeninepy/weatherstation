#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_BMP3XX.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_INA260.h>
#include <WiFiS3.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <SD.h>
#include "RTC.h"


#define OLED_DC    5  // Connect to the DC (Data/Command) pin of the OLED display
#define OLED_CS    6  // Connect to the CS (Chip Select) pin of the OLED display
#define OLED_RESET 7   // Connect to the RST (Reset) pin of the OLED display
const int chipSelect = 4;
const char* ssid     = "Hubbard Express 5G";
const char* password = "3300719731973";
const int uvSensorPin = A0;
int anemometerPin = A2;

WiFiServer server(80);
Adafruit_SSD1306 display(128, 64, &Wire);
File dataFile;

Adafruit_BMP3XX bmp;
Adafruit_AHTX0 aht;
Adafruit_INA260 ina260 = Adafruit_INA260();


// Converting from raw voltage to UV light reading
float convertToUVIndex(int rawReading) {
  float voltage = (rawReading / 1023.0) * 5.0;
  float uvIndex = voltage / 0.1;
  return uvIndex;
}
// Converting from raw voltage to Wind Speed
float getWindSpeed() {
  int sensorValue = analogRead(anemometerPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float windSpeed = voltage / 0.04;
  return windSpeed;
}
void setup() {
  // Start the serial communication
  Serial.begin(115200);
  while (!Serial); // for boards that support it, wait for serial port to connect.

  // Begin WiFi connection
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin("Hubbard Express", "3300719731973");

  // Wait for connection and print the status every second
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Error code ");
    Serial.println(WiFi.status());
  }
  // Connect to WiFi and print the IP address to connect to
  Serial.println(""); // Print a new line
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
    // Start OLED display
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x77)) {
      Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.clearDisplay();
  // Start sensors on I2C communication
  if (!SD.begin(4)) {
    while (1);
  }
  if (!bmp.begin_I2C()) {
    while (1);
  }
  if (!aht.begin()) {
    while (1);
  }
  if (!ina260.begin()) {
    while (1);
  }

  RTC.begin();
}

void loop() {
  //check for client connection, if client is connected, then print to website.
  WiFiClient client = server.available();
  if (client) {
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
            float windSpeed = getWindSpeed();
            handleRoot(client, windSpeed);
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
  }
  // convert raw voltage to voltage used and wind speed
  int rawReading = analogRead(anemometerPin);
  float voltage = (rawReading / 1023.0) * 5.0;
  float windSpeed = (voltage - 0.4) * (32.4 / (2.0 - 0.4));

  // get current time, day, month, hour, and year
  RTCTime currenttime;
  RTC.getTime(currenttime);
  String currentDate = String(currenttime.getDayOfMonth()) + "/" + String(Month2int(currenttime.getMonth())) + "/" + String(currenttime.getYear());
  String currentTime = String(currenttime.getHour()) + ":" + String(currenttime.getMinutes()) + ":" + String(currenttime.getSeconds());
  
  //  define all sensor varibles
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0F;
  float tempF = temperature * 9.0 / 5.0 + 32;
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  float humidityValue = humidity.relative_humidity;
  int uvSensorReading = analogRead(uvSensorPin);
  float uvIndex = convertToUVIndex(uvSensorReading);
  float current = ina260.readCurrent();
  float power = ina260.readPower();
  float windChill = 35.74 + 0.6215 * temperature - 35.75 * pow(windSpeed, 0.16) + 0.4275 * temperature * pow(windSpeed, 0.16);
  float dewPoint = temperature - ((100 - humidityValue)/5);
  float heatIndex = -42.379 +
                  2.04901523 * tempF +
                  10.14333127 * humidityValue -
                  0.22475541 * tempF * humidityValue -
                  0.00683783 * tempF * tempF -
                  0.05481717 * humidityValue * humidityValue +
                  0.00122874 * tempF * tempF * humidityValue +
                  0.00085282 * tempF * humidityValue * humidityValue -
                  0.00000199 * tempF * tempF * humidityValue * humidityValue;
  // print all sensor values to serial moniter
  Serial.print("Date: "); Serial.print(currentDate); Serial.println("");
  Serial.print("Time: "); Serial.print(currentTime); Serial.println("");
  Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" C");
  Serial.print("Temperature: "); Serial.print(tempF); Serial.println(" F");
  Serial.print("Power: "); Serial.print(power); Serial.println(" mW");
  Serial.print("Pressure: "); Serial.print(pressure); Serial.println(" hPa");
  Serial.print("Humidity: "); Serial.print(humidityValue); Serial.println(" %");
  Serial.print("UV Index: "); Serial.print(uvIndex); Serial.println();
  Serial.print("Wind Speed: "); Serial.print(windSpeed); Serial.println(" m/s");
  Serial.print("Dew Point"); Serial.print(dewPoint); Serial.println(" F");
  Serial.print("Wind Chill: "); Serial.print(windChill); Serial.println(" F");

  
  // print all sensor data to OLED screen
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print(F("Date: ")); display.println(currentDate);
  display.print(F("Time: ")); display.println(currentTime);
  display.print(F("Temp: ")); display.print(temperature); display.println(F(" C"));
  display.print(F("Temp: ")); display.print(tempF); display.println(F(" F"));
  display.print(F("Pres: ")); display.print(pressure); display.println(F(" hPa"));
  display.print(F("Hum: ")); display.print(humidityValue); display.println(F(" %"));
  display.print(F("Curr: ")); display.print(current); display.println(F(" mA"));
  display.print(F("Pow: ")); display.print(power); display.println(F(" mW"));
  display.print(F("UV Index: ")); display.print(uvIndex); display.println();
  display.print(F("Wind Speed: ")); display.print(windSpeed); display.println(F(" m/s"));
  display.print(F("Wind Chill:  ")); display.print(windChill); display.println(F(" C"));
  display.print(F("Dew Point ")); display.print(dewPoint); display.println(F(" F"));

  display.display();
  //log all info to sd card, if it is detected
  dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.print(currentDate); dataFile.print(F(" "));
    dataFile.print(currentTime); dataFile.print(F(","));
    dataFile.print(temperature); dataFile.print(F(","));
    dataFile.print(tempF); dataFile.print(F(","));
    dataFile.print(pressure); dataFile.print(F(","));
    dataFile.print(humidityValue); dataFile.print(F(","));
    dataFile.print(current); dataFile.print(F(","));
    dataFile.print(uvIndex); dataFile.print(F(","));
    dataFile.print(windSpeed); dataFile.print(F(","));
    dataFile.print(windChill); dataFile.print(F(","));
    dataFile.print(dewPoint); dataFile.print(F(","));
    dataFile.println(power);
    dataFile.close();
  }

  delay(2000);
}

//code to print info to website
void handleRoot(WiFiClient client, float windSpeed) {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);  
  float humidityValue = humidity.relative_humidity;
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0F;
  float current = ina260.readCurrent();
  float power = ina260.readPower();
  int uvSensorReading = analogRead(uvSensorPin); 
  float uvIndex = convertToUVIndex(uvSensorReading);
  float windChill = 35.74 + 0.6215 * temperature - 35.75 * pow(windSpeed, 0.16) + 0.4275 * temperature * pow(windSpeed, 0.16);
  float dewPoint = temperature - ((100 - humidityValue)/5);
  float tempF = temperature * 9.0 / 5.0 + 32;
  float heatIndex = -42.379 +
                  2.04901523 * tempF +
                  10.14333127 * humidityValue -
                  0.22475541 * tempF * humidityValue -
                  0.00683783 * tempF * tempF -
                  0.05481717 * humidityValue * humidityValue +
                  0.00122874 * tempF * tempF * humidityValue +
                  0.00085282 * tempF * humidityValue * humidityValue -
                  0.00000199 * tempF * tempF * humidityValue * humidityValue;
  String html = "<!DOCTYPE HTML><html><head><title>Arduino Sensor Data</title><style>"
                "body { font-family: Arial, sans-serif; background-color: #f0f0f0; margin: 0; padding: 20px; }"
                ".container { background-color: #ffffff; padding: 20px; border-radius: 10px; margin: auto; width: 50%; }"
                "h1 { color: #333; }"
                "p { font-size: 1.25em; }"
                "</style></head><body><div class='container'><h1>Sensor Data</h1>"
                "<p>Temperature: " + String(temperature) + " (C)</p>"
                "<p>Temperature: " + String(tempF) + " (F)</p>"
                "<p>Pressure: " + String(pressure) + " hPa</p>"
                "<p>Humidity: " + String(humidityValue) + " %</p>"
                "<p>Current: " + String(current) + " mA</p>"
                "<p>Power: " + String(power) + " mW</p>"
                "<p>UV Index: " + String(uvIndex) + "</p>";
                "<p>Wind Speed: " + String(windSpeed) + " m/s</p>";
                "<p>Wind Speed: " + String(windChill) + " m/s</p>";
                "<p>Wind Speed: " + String(dewPoint) + " m/s</p>";
                "</div></body></html>";
  client.print(html);
  client.stop();
}
