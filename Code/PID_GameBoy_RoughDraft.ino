#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16, 2);

int brightness;

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

#define PID_ENABLE_SWITCH_PIN 13
bool startSwitchState;
bool PIDEnabled;
bool wasPIDEnabled;

#define POTENTIOMETER_PIN A3
#define TRANSISTOR_PIN 11
int motorSetpointValue;
int motorInputValue;

#define PHOTO_PIN 2
long time = 0;
long oldTime = 0;
long rpm;
int photoCount = 0;

long error = 0;
long previous_error = 0;
long integral = 0;
long derivative = 0;
long drive = 0;
const int kP = 1;
const int kI = 1;
const int kD = 1;

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
	lcd.setBacklight(brightness);

	attachInterrupt(digitalPinToInterrupt(PHOTO_PIN), check, CHANGE);
}

void loop() {
	time = millis();

	// Button Increase
	AButtonState = digitalRead(A_BUTTON_PIN);
	if (AButtonState == true) {
		brightness++;
	}
	// Button Decrease
	BButtonState = digitalRead(B_BUTTON_PIN);
	if (BButtonState == true) {
		brightness--;
	}

	// LED Switch
	ledSwitchState = digitalRead(SELECT_PIN);
	if (ledSwitchState == true) {
		analogWrite(LED_BACKLIGHT_PIN, brightness);
	} else {
		analogWrite(LED_BACKLIGHT_PIN, 0);
	}

	// Get potentiometer value
	motorSetpointValue = analogRead(POTENTIOMETER_PIN);

	// Enable PID
	startSwitchState = digitalRead(PID_ENABLE_SWITCH_PIN);
	if (startSwitchState == true) {
		PIDEnabled = true;
		if (wasPIDEnabled == false) {
			LCD_delay = 1000;
			wasPIDEnabled = true;
		} 
	} else {
		PIDEnabled = false;
		if (wasPIDEnabled == true) {
			LCD_delay = 1000;
			wasPIDEnabled = false;
		}
	}

	// LCD
	lcd.setBacklight(brightness);
	lcd.setCursor(0,0);
	if (LCD_delay <= 0) {
		lcd.print("Input Speed:");
		lcd.print(motorSetpointValue);
	} else {
		if (PIDEnabled == true) {
			lcd.print("PID Enabled");
		} else {
		LCD_delay--;
			lcd.print("PID Disabled");
		}
	}

	// RPM / PID Math
	if (time - oldTime > 1000) {
		detachInterrupt(digitalPinToInterrupt(PHOTO_PIN));
		// RPM Math
		rpm = (photoCount/(time - oldTime)) * 1000 * 60;
		lcd.setCursor(0,1);
		if (LCD_delay <= 0) {
			lcd.print("Actual Speed:");
			lcd.print(rpm);
		}
		photoCount = 0;
		oldTime = time;
		// PID Math
		if (PIDEnabled == true) {
			error = motorSetpointValue - rpm;
			integral += error;
			derivative = error - previous_error;
			drive = error*kP + integral*kI + derivative*kP;
			previous_error = error;
			// wait(dt);
		} else {
			error = motorSetpointValue - rpm;
			drive = error*kP;

		}
		attachInterrupt(digitalPinToInterrupt(PHOTO_PIN), check, CHANGE);
	}

	// Output to Motor
	motorInputValue = map(motorSetpointValue, 0, 1023, 0, 255);
	analogWrite(TRANSISTOR_PIN, motorInputValue);

	delay(30);
	lcd.clear();
}


void check() {
	++photoCount;
}
