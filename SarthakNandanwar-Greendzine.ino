//
//
// Author:  Sarthak Nandanwar 
// Subject: Firmware Assignment for Greendzine internship position. 
//
//
//



#include <TimerOne.h>

const int lm35Pin = A0;                             // LM35 temperature sensor connected to Analog pin A0
const int ledPin = 13;                              // Onboard LED connected to digital pin 13

const int thresholdTemp = 30;                       // Temperature threshold below which LED blinks every 250 ms and above which LED blinks every 500 ms

int temperature;                                    // Storing temperature reading from LM35 sensor


void setup() {
  pinMode(ledPin, OUTPUT);                          // Set the LED pin as an output

  // Set up Timer1 with a period of 1 second
  Timer1.initialize(1000000);                       // 1000000 milliseconds converted to seconds
  
  // Run the blink_LED function according to the Timer1 interrupt
  Timer1.attachInterrupt(blink_LED);
}

void loop() {
  temperature = readTemperature();                  // Read temperature from LM35 sensor

  // Check temperature and set blink interval accordingly
  if (temperature < thresholdTemp) {
      Timer1.setPeriod(250000);                     // 250 ms in microseconds
      Timer1.attachInterrupt(blink_LED);            // Below 30 degrees Celsius, blink every 250 ms
  } 


  if (temperature > thresholdTemp) {
      Timer1.setPeriod(500000);                     // 500 ms in microseconds
      Timer1.attachInterrupt(blink_LED);            // Above 30 degrees Celsius, blink every 500 ms
  }

}


void blink_LED() {
  // Toggle the state of the LED
  digitalWrite(ledPin, !digitalRead(ledPin));
}

int readTemperature() {
  
  // Read the analog value from LM35 and convert it to temperature in Celsius
  int sensor_Value = analogRead(lm35Pin);
  float voltage = (sensor_Value / 1024.0) * 5.0;
  float temperatureCelsius = (voltage) * 100.0;

  return temperatureCelsius;

}