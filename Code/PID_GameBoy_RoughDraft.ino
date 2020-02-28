LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7);

int brightness;

#define LED_SWITCH_PIN 12
bool LED_SWITCH_STATE;
#define LED_BACKLIGHT_PIN 9

#define BUTTON_INCREASE_PIN 8
bool BUTTON_INCREASE_STATE;
#define BUTTON_DECREASE_PIN 7
bool BUTTON_DECREASE_STATE;

#define LCD_BACKLIGHT_PIN 3
int LCD_delay = 0;

#define PID_ENABLE_SWITCH_PIN 6 // change this pin to whatever
bool PID_ENABLE_SWITCH_STATE;	
bool PID_enabled;
bool was_PID_enabled;

#define POTENTIOMETER_PIN A0
#define TRANSISTOR_PIN 5 // change this pin to whatever
int MOTOR_SETPOINT_VALUE;
int MOTOR_INPUT_VALUE;

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

	pinMode(LED_SWITCH_PIN, INPUT);
	pinMode(LED_BACKLIGHT_PIN, OUTPUT);

	pinMode(BUTTON_INCREASE_PIN, INPUT);
	pinMode(BUTTON_DECREASE_PIN, INPUT);

	pinMode(PID_ENABLE_SWITCH_PIN, INPUT);
	pinMode(PHOTO_PIN, INPUT);
	pinMode(POTENTIOMETER_PIN, INPUT);

	lcd.begin(16,2);
	lcd.setBacklightPin(LCD_BACKLIGHT_PIN, POSITIVE);
	lcd.setBacklight(brightness);

	attachInterrupt(digitalPinToInterrupt(PHOTO_PIN), check, CHANGE);
}

void loop() {
	time = millis();

	// Button Increase
	BUTTON_INCREASE_STATE = digitalRead(BUTTON_INCREASE_PIN);
	if (BUTTON_INCREASE_STATE == true) {
		brightness++;
	}
	// Button Decrease
	BUTTON_DECREASE_STATE = digitalRead(BUTTON_DECREASE_PIN);
	if (BUTTON_DECREASE_STATE == true) {
		brightness--;
	}

	// LED Switch
	LED_SWITCH_STATE = digitalRead(LED_SWITCH_PIN);
	if (LED_SWITCH_STATE == true) {
		analogWrite(LED_BACKLIGHT_PIN, brightness);
	} else {
		analogWrite(LED_BACKLIGHT_PIN, 0);
	}

	// Get potentiometer value
	MOTOR_SETPOINT_VALUE = analogRead(POTENTIOMETER_PIN);

	// Enable PID
	PID_ENABLE_SWITCH_STATE = digitalRead(PID_ENABLE_SWITCH_PIN);
	if (PID_ENABLE_SWITCH_STATE == true) {
		PID_enabled = true;
		if (was_PID_enabled == false) {
			LCD_delay = 1000;
			was_PID_enabled = true;
		}
	} else {
		PID_enabled = false;
		if (was_PID_enabled == true) {
			LCD_delay = 1000;
			was_PID_enabled = false;
		}
	}

	// LCD
	lcd.setBacklight(brightness);
	lcd.setCursor(0,0);
	if (LCD_delay <= 0) {
		lcd.print("Input Speed: " + MOTOR_SETPOINT_VALUE + " RPM");
	} else {
		if (PID_enabled == true) {
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
			lcd.print("Actual Speed: " + rpm + " RPM");
		}
		photoCount = 0;
		oldTime = time;
		// PID Math
		if (PID_enabled == true) {
			error = MOTOR_SETPOINT_VALUE - rpm;
			integral += error;
			derivative = error - previous_error;
			drive = error*kP + integral*kI + derivative*kP;
			previous_error = error;
			// wait(dt);
		} else {
			error = MOTOR_SETPOINT_VALUE - rpm;
			drive = error*kP;

		}
		attachInterrupt(digitalPinToInterrupt(PHOTO_PIN), check, CHANGE);
	}

	// Output to Motor
	MOTOR_INPUT_VALUE = map(MOTOR_SETPOINT_VALUE, 0, 1023, 0, 255);
	analogWrite(TRANSISTOR_PIN, MOTOR_INPUT_VALUE);

	delay(30);
	lcd.clear();
}

void check() {
	++photoCount;
}