#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <WiFiManager.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

// HTTP Client
String serverName = "https://api.publicapis.org/entries";

unsigned long lastTime = 0;
unsigned long lastTimeGetAction = 0;
unsigned long timerDelay = 10000;
unsigned long timerDelayAction = 1000;

// pin moisture
#define SOIL_1 32
#define SOIL_2 33

// pin suhu
#define DS18B20PIN1 18
#define DS18B20PIN2 19

// variable moisture
const int dry_1 = 3152;
const int dry_2 = 3125;
const int wet_1 = 1712;
const int wet_2 = 1563;

int pinButton = 25;

// Sensor action
String sensorActionReading;
String sensor1Action;
String sensor2Action;
JSONVar actionObject;

// variable suhu
OneWire oneWire(DS18B20PIN1);
OneWire twoWire(DS18B20PIN2);
DallasTemperature sensorSuhu1(&oneWire);
DallasTemperature sensorSuhu2(&twoWire);
LiquidCrystal_I2C lcd(0x27, 16, 2);
float tempC1;
float tempC2;
int percentageHumidity_1;
int percentageHumidity_2;
byte degree_symbol[8] = 
              {
                0b00111,
                0b00101,
                0b00111,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000
              };

// millis moisture
unsigned long beforeMoisture = 0;
bool moistureStatus = false;
unsigned long intervalMoisture = 1000;

int i = 0;
bool buttonState = false;

unsigned long lcdNow;
unsigned long lcdThen;

// millis suhu
unsigned long beforeSuhu = 0;
bool suhuStatus = false;
unsigned long intervalSuhu = 1000;

// Inisiasi fungsi
void suhuStart();
void moistureStart();
void postDataSoil();
String soilAction();



void IRAM_ATTR toggleButtonState()
{
  buttonState = true;
}


void setup() {
  Serial.begin(115200);

  pinMode(pinButton, INPUT_PULLUP);

  //  Wifi Manager
  WiFi.mode(WIFI_STA);

  WiFiManager wm;

  // reset setting
  // wm.resetSetting();

  bool res;
  res = wm.autoConnect("ESP32-SOIL STATION JAHE", "");

  // Start the LCD
  lcd.begin();
  lcd.backlight();
  lcd.createChar(0, degree_symbol);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Not connected");

  if (!res) {
    Serial.println("Failed to connect");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Failed to connect");
    delay(3000);
    // ESP.restart();
  } else {
    Serial.println("Connected!");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Connected!");
    delay(3000);
  }

  /* Start the DS18B20 Sensor */
  sensorSuhu1.begin();
  sensorSuhu2.begin();

  attachInterrupt(pinButton, toggleButtonState, CHANGE);
}

void loop() {
  sensorActionReading = soilAction();
  actionObject = JSON.parse(sensorActionReading);
  
  String sensorAction1Main = actionObject[0]["sensor1"];
  String sensorAction2Main = actionObject[0]["sensor2"];
  
  Serial.println(digitalRead(pinButton));
  lcdNow = millis();
  suhuStart();
  moistureStart();
  if (sensorAction1Main == "on" && sensorAction2Main != "on") {
    postDataSoil();
  } else if (sensorAction1Main != "on" && sensorAction2Main == "on") {
    postDataSoil();
  } else if (sensorAction1Main == "on" && sensorAction2Main == "on") {
    postDataSoil();
  }

  if(buttonState){
    i++;
    buttonState = false;
  }
//  if (lcdNow - lcdThen > 2000) {
//    lcdThen = lcdNow;
//    i++;
//  }



  switch(i){
  case 1:
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hum1=");
  lcd.print(percentageHumidity_1);
  lcd.print("%");

  lcd.setCursor(0,1);
  lcd.print("Hum2=");
  lcd.print(percentageHumidity_2);
  lcd.print("%");
  break;

  case 2:
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp1 = ");
  lcd.print(tempC1);
  lcd.write(0);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Temp2 = ");
  lcd.print(tempC2);
  lcd.write(0);
  lcd.print("C");

  break;

  default:
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SOIL STATION");
  lcd.setCursor(0,1);
  lcd.print("TRK SV IPB 57");
  i = 0;
  break;
  }
}
