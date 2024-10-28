// Distance Sensor Definitions
#define BUZZER_PIN 2
#define TRIG_PIN 5
#define ECHO_PIN 18
#define LED_PIN 4           // Define the LED pin
#define MAX_DISTANCE 100     // Maximum distance threshold (100 cm)

// Temperature Sensor Definitions
#define ADC_VREF_mV 3300.0   // ESP32's ADC reference voltage in millivolts
#define ADC_RESOLUTION 4095.0 // ESP32's ADC resolution (12-bit)
#define PIN_LM35 33          // Pin connected to LM35 sensor
#define TEMP_THRESHOLD 40.0  // Temperature threshold in °C for buzzer

void setup() {
  // Distance Sensor Setup
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);  // Set LED pin as output
  Serial.begin(115200);      // Initialize serial communication for distance readings

  // Temperature Sensor Setup
  Serial.begin(9600);        // Initialize serial communication for temperature readings
}

long readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);      // Standard 10us pulse width
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 6000);  // Timeout for 1 meter (6ms)
  
  // If duration is 0, no echo was received, return 0 cm
  if (duration == 0) {
    return 0;  // No object detected
  }

  // Convert the time into a distance in cm
  long distance = duration * 0.034 / 2;

  // Return distance if it's less than the maximum distance threshold
  if (distance <= MAX_DISTANCE) {
    return distance;
  } else {
    return 0;  // Return 0 if the distance is out of valid range
  }
}

void loop() {
  // Distance Measurement
  long distance = readDistance();
  
  // Print the distance
  if (distance > 0) {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  } else {
    Serial.println("No object detected");
  }

  // Temperature Measurement
  int adcVal = analogRead(PIN_LM35);  // Read the ADC value from the LM35
  
  // Convert ADC value to voltage in millivolts
  float milliVolt = (adcVal * ADC_VREF_mV) / ADC_RESOLUTION;

  // Convert voltage to temperature (LM35 gives 10mV per degree Celsius)
  float tempC = milliVolt / 10.0;
  float tempF = tempC * 9.0 / 5.0 + 32.0;

  // Print ADC value, temperature in both Celsius and Fahrenheit
  Serial.print("ADC Value: ");
  Serial.println(adcVal);
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print("°C");
  Serial.print("  ~  ");
  Serial.print(tempF);
  Serial.println("°F");

  // Activate the buzzer and LED if the object is within 20 cm or if temperature is above 40°C
  if ((distance > 0 && distance < 20) || tempC > TEMP_THRESHOLD) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);  // Turn LED on
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);   // Turn LED off
  }

  delay(2000);  // Delay for 2 seconds between readings
}
