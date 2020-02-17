LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7);

#define LED_SWITCH_PIN 12
bool LED_SWITCH_STATE;
#define LED_BACKLIGHT_PIN 9
#define BUTTON_INCREASE_PIN 8
bool BUTTON_INCREASE_STATE;
#define BUTTON_DECREASE_PIN 7
bool BUTTON_DECREASE_STATE;
int brightness;
#define LCD_BACKLIGHT_PIN 3

// temporarily unorganized vars
#define PID_ENABLE_SWITCH_PIN 6; // change this pin to whatever
bool PID_ENABLE_SWITCH_STATE;
bool PID_enabled;

void setup() {
	Serial.begin(9600);

	pinMode(LED_SWITCH_PIN, INPUT);
	pinMode(LED_BACKLIGHT_PIN, OUTPUT);

	pinMode(BUTTON_INCREASE_PIN, INPUT);
	pinMode(BUTTON_DECREASE_PIN, INPUT);

	lcd.begin(16,2);
	lcd.setBacklightPin(LCD_BACKLIGHT_PIN, POSITIVE);
	lcd.setBacklight(brightness);
}

void loop() {
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

	// LCD
	lcd.setBacklight(brightness);

	// PID
	PID_ENABLE_SWITCH_STATE = digitalRead(PID_ENABLE_SWITCH_PIN);
	if (PID_ENABLE_SWITCH_STATE == true) {
		PID_enabled = true;
	} else {
		PID_enabled = false;
	}
}