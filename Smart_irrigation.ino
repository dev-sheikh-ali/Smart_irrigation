
#define soilWet 500    // 'Wet'
#define soilDry 750   // 'dry'

#include <Servo.h>
#include <LiquidCrystal_I2C.h>

// Sensor pins
#define sensorPower 7
#define sensorPin A0

Servo myservo;
LiquidCrystal_I2C lcd(0x27, 16, 2); 
int pump = 90;


void setup()
{
  pinMode(sensorPower, OUTPUT);
	// Initially keep the sensor OFF
	digitalWrite(sensorPower, LOW);

  myservo.attach(6);
  lcd.init(); 
  lcd.backlight();
  Serial.begin(9600);
  myservo.write(pump);
  delay(1000);
 
}

void loop()
{

	int moisture = readSensor();
	Serial.print("Analog Output: ");
	Serial.println(moisture);

	// Determine status of our soil
	if (moisture < soilWet) {
    pump = pump-30;
		Serial.println("Soil too wet");
    lcd.clear();                 
    lcd.setCursor(0, 0);
    lcd.print("Soil too wet "); 
	} else if (moisture >= soilWet && moisture < soilDry) {
		Serial.println("Soil is perfect");
    lcd.clear();                 
    lcd.setCursor(0, 0);
    lcd.print("soil is perfect "); 
	} else {
		Serial.println("Status: Soil is too dry - time to water!");
    pump = pump-30;
		Serial.println("Soil is too dry");
    lcd.clear();                 
    lcd.setCursor(0, 0);
    lcd.print("Soil is too dry");
	}
	
	delay(1000);	// Take a reading every second for testing
					// Normally you should take reading perhaps once or twice a day
	Serial.println();

  
  if(pump > 170) { pump = 170; } 
  if(pump < 0) { pump = 0; } 

  myservo.write(pump); // write the position to servo
  delay(100);
  
}

int readSensor() {
	digitalWrite(sensorPower, HIGH);	// sensor ON
	delay(10);							// Allow power to settle
	int val = analogRead(sensorPin);	// Read the analog value form sensor
	digitalWrite(sensorPower, LOW);		// Turn the sensor OFF
	return val;							// Return analog moisture value
}