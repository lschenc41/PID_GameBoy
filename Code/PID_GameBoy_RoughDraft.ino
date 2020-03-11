#include <Wire.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16, 2);

int brightness = 128;

#define SELECT_PIN 12 // turns led on/off
bool ledSwitchState;
#define LED_BACKLIGHT_PIN 3

#define A_BUTTON_PIN 7 //Turns Up Brightness
bool AButtonState;
bool pastAButtonState;

#define B_BUTTON_PIN 8 //Turns Down Brightness
bool BButtonState;
bool pastBButtonState;

int LCD_delay = 0;
int past_LCD_delay = 0;

#define PID_ENABLE_SWITCH_PIN 13
bool startSwitchState;
bool PIDEnabled;
bool wasPIDEnabled = false;

#define POTENTIOMETER_PIN A3
#define TRANSISTOR_PIN 11
int motorSetpointValue;
int motorInputValue;

#define PHOTO_PIN 2
long time = 0;
long oldTime = 0;
long rpm = 0;
int photoCount = 0;

long error = 0;
long previous_error = 0;
long integral = 0;
long derivative = 0;
long drive = 0;
const int kp = 1;
const int ki = 1;
const int kd = 1;


void setup() {
	Serial.begin(9600);

	pinMode(SELECT_PIN, INPUT);
	pinMode(LED_BACKLIGHT_PIN, OUTPUT);

	pinMode(A_BUTTON_PIN, INPUT);
	pinMode(B_BUTTON_PIN, INPUT);

	pinMode(PID_ENABLE_SWITCH_PIN, INPUT);
	pinMode(PHOTO_PIN, INPUT);
	pinMode(POTENTIOMETER_PIN, INPUT);

	lcd.begin(16,2);
	lcd.init();
	lcd.setBacklight(brightness);

	lcd.setCursor(4,0);
	//sets pos to print to
	//0,0 is the very top left. (Column[0-15], row[0-1])
	lcd.print("Nintendo");
	delay(1000);
	delay(1000);
	lcd.setCursor(1,1);
	lcd.print("Just Kidding:)");
	delay(1500);
	lcd.clear();
	delay(1500);
	lcd.setCursor(0,0);
	lcd.print("PID Box by:lsche");
	lcd.setCursor(0,1);
	lcd.print("nc41, jkammau97");
	delay(3000);
	lcd.clear();
	
	attachInterrupt(digitalPinToInterrupt(PHOTO_PIN), check, CHANGE);

	analogWrite(LED_BACKLIGHT_PIN, 255);
}

void loop() {
	time = millis();

	// Button Increase
	AButtonState = digitalRead(A_BUTTON_PIN);
	if (AButtonState == true) {
		brightness = brightness - 20;
	}
	// Button Decrease
	BButtonState = digitalRead(B_BUTTON_PIN);
	if (BButtonState == true) {
		brightness = brightness - 20;
	}

	// LED Switch
	ledSwitchState = digitalRead(SELECT_PIN);
	if (ledSwitchState != true) {
		analogWrite(LED_BACKLIGHT_PIN, 255);
	} else {
		//analogWrite(LED_BACKLIGHT_PIN, 0);
	}

	// Get potentiometer value
	motorSetpointValue = (analogRead(POTENTIOMETER_PIN)*100)/1023;

	// Enable PID
	startSwitchState = digitalRead(PID_ENABLE_SWITCH_PIN);
	if (startSwitchState == true) {
		PIDEnabled = true;
		if (wasPIDEnabled == false) {
			LCD_delay = 3;
			lcd.clear();
			wasPIDEnabled = true;
		} 
	} else {
		PIDEnabled = false;
		if (wasPIDEnabled == true) {
			LCD_delay = 3;
			lcd.clear();
			wasPIDEnabled = false;
		}
	}

	// LCD
	lcd.setBacklight(brightness);
	lcd.setCursor(0,0);
	if (LCD_delay > 0) {
		if (PIDEnabled == true) {
			lcd.print(" PID Enabled");
		} else {
			lcd.print(" PID Disabled");
		}
	} else {
		if (past_LCD_delay > 0) {
			lcd.clear();
		}
		lcd.print(" Input: ");
		lcd.print(motorSetpointValue);
		lcd.print("   ");
	}

	// RPM / PID Math
	if (time - oldTime > 1000) {
		detachInterrupt(digitalPinToInterrupt(PHOTO_PIN));
		// RPM Math
		rpm = (photoCount/(time - oldTime)) * 1000 * 60;
		lcd.setCursor(0,1);
		if (LCD_delay <= 0) {
			lcd.print(" Actual: ");
			lcd.print(rpm);
			lcd.print("   ");
		}
		photoCount = 0;
		oldTime = time;
		// PID Math
		if (PIDEnabled == true) {
			error = motorSetpointValue - rpm;
			integral += error;
			derivative = error - previous_error;
			drive = error*kp + integral*ki + derivative*kd;
			previous_error = error;
			// wait(dt);
		} else {
			error = motorSetpointValue - rpm;
			drive = error*kp;

		}
		attachInterrupt(digitalPinToInterrupt(PHOTO_PIN), check, CHANGE);
	}

	// Output to Motor
	motorInputValue = motorSetpointValue*2.55;
	analogWrite(TRANSISTOR_PIN, motorInputValue);

	past_LCD_delay = LCD_delay;
	if (LCD_delay > 0) {
		LCD_delay--;
	}

	delay(500);
}


void check() {
	++photoCount;
}
