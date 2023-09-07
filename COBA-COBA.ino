#define AOUT_PIN 26 // ESP32 pin GPIO36 (ADC0) that connects to AOUT pin of moisture sensor

void setup() {
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(AOUT_PIN); // read the analog value from sensor

  Serial.print("Moisture value: ");
  Serial.println(value);

  delay(500);
}
