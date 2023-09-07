#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define DS18B20PIN 27

OneWire oneWire(DS18B20PIN);
DallasTemperature sensorSuhu(&oneWire);
LiquidCrystal_I2C lcd(0x27, 16, 2);
float tempC;
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

// millis
unsigned long beforeSuhu = 0;
bool suhuStatus = false;
unsigned long intervalSuhu = 500;

void setup() {
   Serial.begin(115200);

  /* Start the DS18B20 Sensor */
  sensorSuhu.begin();

  // Start the LCD
  lcd.begin();
  lcd.backlight();
  lcd.createChar(0, degree_symbol);
  lcd.setCursor(0,0);
  lcd.print(" DS18B20  with ");
  lcd.setCursor(0,1);
  lcd.print("  ESP32 DevKit ");
  delay(2000);
}

void loop() {
  suhuStart();
}

void suhuStart() {
  // hitung selisih waktu
  unsigned long waktuSekarang = millis();

  if (waktuSekarang - beforeSuhu > intervalSuhu) {
    suhuStatus = !suhuStatus;

    if (suhuStatus) {
      sensorSuhu.requestTemperatures();
      tempC = constrain(sensorSuhu.getTempCByIndex(0), 0, 100);
      lcd.setCursor(0,0);
      lcd.print("Temp = ");
      lcd.print(tempC);
      lcd.write(0);
      lcd.print("C");
      Serial.print("Temperature = ");
      Serial.print(tempC);
      Serial.println("°C");
    }

    beforeSuhu = waktuSekarang;
  }
}
