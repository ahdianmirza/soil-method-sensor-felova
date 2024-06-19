#define SOIL_1 32 // ESP32 pin GPIO36 (ADC0) that connects to AOUT pin of moisture sensor
#define SOIL_2 33

const int dry_1 = 3152;
const int dry_2 = 3125;
const int wet_1 = 1712;
const int wet_2 = 1563;

void setup() {
  Serial.begin(115200);
}

void loop() {
  int sensorVal_1 = analogRead(SOIL_1); // read the analog value from sensor
  int sensorVal_2 = analogRead(SOIL_2);

  int hum_value1 = (sensorVal_1 - 3119.7) / (-17.307);
  int hum_value2 = (sensorVal_2 - 3076.9) / (-16.306);

//  int percentageHumidity_1 = constrain(map(sensorVal_1, wet_1, dry_1, 100, 0), 0, 100);
//  int percentageHumidity_2 = constrain(map(sensorVal_2, wet_2, dry_2, 100, 0), 0, 100);

  int percentageHumidity_1 = constrain(hum_value1, 0, 100);
  int percentageHumidity_2 = constrain(hum_value2, 0, 100);
  
//  Serial.print("Moisture percentage 1: ");
//  Serial.print(percentageHumidity_1);
//  Serial.println("%");
//
//  Serial.print("Moisture percentage 2: ");
//  Serial.print(percentageHumidity_2);
//  Serial.println("%");

  Serial.print("Moisture ADC 1: "); Serial.println(percentageHumidity_1);
  Serial.print("Moisture ADC 2: "); Serial.println(percentageHumidity_2);

  delay(1000);
}
