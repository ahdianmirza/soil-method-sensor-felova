#define SOIL_1 25 // ESP32 pin GPIO36 (ADC0) that connects to AOUT pin of moisture sensor
#define SOIL_2 26

const int dry_1 = 3152;
const int dry_2 = 3125;
const int wet_1 = 1712;
const int wet_2 = 1563;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorVal_1 = analogRead(SOIL_1); // read the analog value from sensor
  int sensorVal_2 = analogRead(SOIL_2);

  int percentageHumidity_1 = constrain(map(sensorVal_1, wet_1, dry_1, 100, 0), 0, 100);
  int percentageHumidity_2 = constrain(map(sensorVal_2, wet_2, dry_2, 100, 0), 0, 100);
  
  Serial.print("Moisture percentage 1: ");
  Serial.print(percentageHumidity_1);
  Serial.println("%");

  Serial.print("Moisture percentage 2: ");
  Serial.print(percentageHumidity_2);
  Serial.println("%");

  delay(500);
}
