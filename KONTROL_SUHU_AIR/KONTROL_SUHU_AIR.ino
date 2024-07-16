#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 

const char* ssid = "XXXXXX";
const char* password = "XXXXX";
#define ONE_WIRE_BUS 2
#define BOTtoken "XXXXXX:XXXXXXX"
#define CHAT_ID "XXXXXXX"


OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200); 
  pinMode (2, INPUT_PULLUP);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  
  lcd.init();
  lcd.backlight();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected"); 
  sensors.begin();
}

void loop() {
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); 
  Serial.println("DONE");
  float tempC = sensors.getTempCByIndex(0);

  if(tempC != DEVICE_DISCONNECTED_C) 
  {
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(tempC);
    lcd.clear(); 
    lcd.setCursor(0, 0);
    lcd.print("Suhu Air: ");
    lcd.print(tempC);
    lcd.print(" C");
    
    if(tempC > 35 || tempC > 125) { 
      String message = "PERINGATAN!\n";
      message += "Suhu Air Aquarium Terlalu Tinggi: " + String(tempC, 2) + " °C";
      bot.sendMessage(CHAT_ID, message, "");
    }
  }
  else
  {
    Serial.println("Error: Could not read temperature data");
  }
  delay(5000);
}

// Download ArduinoJson.h di library store
//Jesin Driver Usb FTDI bukan CH340
