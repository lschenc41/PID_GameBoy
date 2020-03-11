//potentiometer.ino
#include <Wire.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>

#define ANALOG_PIN A1
#define LED_PIN 3 //to OUTPUT analog values, must be pin with a ~
float brightness; //the value read by A1 from the potentiometer
// which is then mapped to a value that is proportional between [0,255]

LiquidCrystal_I2C lcd(0x27,16,2);
// sometimes 0x27 works when 0x3F doesn't
// that's the I2C address of the backpack 
void setup()
{
	Serial.begin(9600);
	pinMode(LED_PIN, OUTPUT);
	pinMode(ANALOG_PIN, INPUT);

	lcd.begin (16,2); // for 16 x 2 LCD module
	lcd.init(); //Tells the lcd to get ready to recieve info
	lcd.backlight(); //starts up the backlight
	lcd.setBacklight(HIGH); //turns it on
	lcd.setCursor(0,0);
	lcd.print("POWER");
	delay(100);
}

void loop()
{
	brightness = analogRead(ANALOG_PIN);
	lcd.setCursor(0,1);
	lcd.print(map(brightness,0,1023,0,1000)/100); //funky math. also map only deals with integers, i'll make my own later
	analogWrite(LED_PIN, map(brightness,0,1023,0,25500)/100);
	delay(100);
	lcd.print("          ");
}

