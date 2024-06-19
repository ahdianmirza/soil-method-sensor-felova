void postDataSoil() {
    if((millis() - lastTime > timerDelay)) {
        if (WiFi.status() == WL_CONNECTED) {
            float temp_1, temp_2;
            int hum_1, hum_2;
            String sensor1ActionPost = actionObject[0]["sensor1"];
            String sensor2ActionPost = actionObject[0]["sensor2"];
            String postData;

            temp_1 = tempC1;
            temp_2 = tempC2;
            hum_1 = percentageHumidity_1;
            hum_2 = percentageHumidity_2;

            if (sensor1ActionPost == "on" && sensor2ActionPost != "on") {
              postData = "temp_1=" + String(temp_1) + "&temp_2=" + String(0) + "&hum_1=" + String(hum_1) + "&hum_2=" + String(0);
            } else if (sensor1ActionPost != "on" && sensor2ActionPost == "on") {
              postData = "temp_1=" + String(0) + "&temp_2=" + String(temp_2) + "&hum_1=" + String(0) + "&hum_2=" + String(hum_2);
            } else if (sensor1ActionPost == "on" && sensor2ActionPost == "on") {
              postData = "temp_1=" + String(temp_1) + "&temp_2=" + String(temp_2) + "&hum_1=" + String(hum_1) + "&hum_2=" + String(hum_2);
            }

            HTTPClient http;
            http.setTimeout(500);
            http.begin("http://felova.my.id/api/data-soil");
            http.addHeader("Content-Type", "application/x-www-form-urlencoded");

            auto httpCode = http.POST(postData);
            String payload = http.getString();

            Serial.println(postData);
            Serial.println(payload);

            http.end();
        } else {
            Serial.println("Wifi Disconnected!");
        }
        lastTime = millis();
    }
}
