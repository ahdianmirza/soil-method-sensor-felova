void moistureStart() {
    // hitung selisih waktu
    unsigned long waktuSekarang = millis();

    if (waktuSekarang - beforeMoisture > intervalMoisture) {
        moistureStatus = !moistureStatus;

        if (moistureStatus) {
            int sensorVal_1 = analogRead(SOIL_1); // read the analog value from sensor
            int sensorVal_2 = analogRead(SOIL_2);

            int hum_value1 = (sensorVal_1 - 3119.7) / (-17.307);
            int hum_value2 = (sensorVal_2 - 3076.9) / (-16.306);

            percentageHumidity_1 = constrain(hum_value1, 0, 100);
            percentageHumidity_2 = constrain(hum_value2, 0, 100);
            
//            lcd.setCursor(0,1);
//            lcd.print("Hum1=");
//            lcd.print(percentageHumidity_1);
//            lcd.print("%");
//
//            lcd.setCursor(9,1);
//            lcd.print("Hum2=");
//            lcd.print(percentageHumidity_2);
//            lcd.print("%");
//
//            Serial.print("Moisture percentage 1: ");
//            Serial.print(percentageHumidity_1);
//            Serial.println("%");
//
//            Serial.print("Moisture percentage 2: ");
//            Serial.print(percentageHumidity_2);
//            Serial.println("%");
        }

        beforeMoisture = waktuSekarang;
    }
}
