void suhuStart() {
  // hitung selisih waktu
  unsigned long waktuSekarang = millis();

  if (waktuSekarang - beforeSuhu > intervalSuhu) {
    suhuStatus = !suhuStatus;

    if (suhuStatus) {
      sensorSuhu1.requestTemperatures();
      sensorSuhu2.requestTemperatures();

      tempC1 = constrain(sensorSuhu1.getTempCByIndex(0), 0, 100);
      tempC2 = constrain(sensorSuhu2.getTempCByIndex(0), 0, 100);

      Serial.print("Temperature1 = ");
      Serial.print(tempC1);
      Serial.println("°C");
      Serial.print("Temperature2 = ");
      Serial.print(tempC2);
      Serial.println("°C");
    }

    beforeSuhu = waktuSekarang;
  }
}
