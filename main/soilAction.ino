String soilAction() {
  if((millis() - lastTimeGetAction > timerDelayAction)) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.setTimeout(500);

        String soilActionData = "{}";
        String serverPath = "http://felova.my.id/api/action-soil";

        http.begin(serverPath.c_str());

        int httpResponseCode = http.GET();
        Serial.print(httpResponseCode);
        Serial.println("httpResponseCode");

        if (httpResponseCode > 0) {
            Serial.print("HTTP Response code : ");
            Serial.println(httpResponseCode);
            soilActionData = http.getString();
        } else {
            Serial.print("Error code : ");
            Serial.print(httpResponseCode);
        }
        http.end();
        return soilActionData;
    } else {
      Serial.println("WIFI Disconnected");
    }
    lastTimeGetAction = millis();
  }
}
