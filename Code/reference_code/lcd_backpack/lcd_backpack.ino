//LCD Backpack.ino
#include <Wire.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>

#define BUTTON_PIN 2
#define SWITCH_PIN 4

int difference; //holds whether to add 1 or subtract 1
bool pastButton; //last known state of button
int n; //number for the counter
bool bPwr; //The read power coming from the button
bool sPwr; //The read power coming from the switch
// either is 0(LOW) or 1(HIGH)
LiquidCrystal_I2C lcd(0x27,16,2);
// sometimes 0x27 works when 0x3F doesn't
// that's the I2C address of the backpack 
void setup() {
// put your setup code here, to run once:
	lcd.begin (16,2); // for 16 x 2 LCD module
	lcd.init();
	lcd.setBacklight(HIGH);
	pinMode(BUTTON_PIN, INPUT);
	pinMode(SWITCH_PIN, INPUT);
	lcd.setCursor(0,0); //sets pos to print to
	//0,0 is the very top left. (Column[0-15], row[0-1])
	lcd.print("Counter");
	n = 0;
	pastButton = 0;
	pastSwitch = 0;
}

void loop() {
// put your main code here, to run repeatedly:
	bPwr = digitalRead(BUTTON_PIN);
	sPwr = digitalRead(SWITCH_PIN);
	if(sPwr == HIGH)
	{
		difference = 1;
	} else 
	{
		difference = -1;
	}
	if(bPwr == HIGH and pastButton == 0)
	{
		n = n + difference;
		lcd.setCursor(0,1);
		lcd.print(n);
		lcd.print("            ");
		//these spaces clear the rest of the tiles on the bottom row of the lcd
		//Without them, when the number goes from 10 to 9, the 0 isn't cleared so it reads as 90
	}
	pastButton = bPwr; //sets the previous state so that only the press increments and not the sustain
}
