// Water Level Monitoring System
// Arduino Uno

const int analogInPin = A5;   // Water level sensor connected to A5

int sensorValue = 0;


// Setup function runs once
void setup() {

  // Declare LED and buzzer pins as outputs
  pinMode(7, OUTPUT);    // Red LED
  pinMode(11, OUTPUT);   // Yellow LED
  pinMode(12, OUTPUT);   // Blue LED
  pinMode(13, OUTPUT);   // Buzzer

  Serial.begin(9600);
}


// Function to control LEDs
void setLEDs(bool red, bool yellow, bool blue) {

  digitalWrite(7, red ? HIGH : LOW);
  digitalWrite(11, yellow ? HIGH : LOW);
  digitalWrite(12, blue ? HIGH : LOW);

}


// Function to control buzzer
void beepBuzzer(int frequency, int duration) {

  tone(13, frequency, duration);

}


// Main program loop
void loop() {

  // Read water level sensor
  sensorValue = analogRead(analogInPin);


  // Display sensor value on Serial Monitor
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);


  // Convert sensor reading to percentage
  int sensorPercentage = map(sensorValue, 0, 700, 0, 100);


  // Display percentage
  Serial.print("Water Level: ");
  Serial.print(sensorPercentage);
  Serial.println("%");


  // Water level below 25%
  if (sensorPercentage < 25) {

    setLEDs(false, false, false);
    noTone(13);

    delay(500);

  }


  // Water level between 25% and 49%
  else if (sensorPercentage >= 25 && sensorPercentage <= 49) {

    setLEDs(true, false, false);
    noTone(13);

    delay(500);

  }


  // Water level between 50% and 99%
  else if (sensorPercentage >= 50 && sensorPercentage <= 99) {

    setLEDs(false, true, false);

    beepBuzzer(600, 100);

    delay(500);

  }


  // Water level 100% or above
  else if (sensorPercentage >= 100) {

    setLEDs(false, false, true);

    beepBuzzer(800, 100);

    delay(100);


    // Continue beeping until water level reduces
    while (sensorPercentage >= 100) {

      beepBuzzer(800, 100);

      delay(100);


      // Read sensor again
      sensorValue = analogRead(analogInPin);


      // Update percentage
      sensorPercentage = map(sensorValue, 0, 700, 0, 100);

    }

  }

}
