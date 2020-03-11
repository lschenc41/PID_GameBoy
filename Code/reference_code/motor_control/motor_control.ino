//Motor_Control

#define ANALOG_PIN A0
#define MOTOR_PIN 11
void setup()
{
	Serial.begin(9600);
	pinMode(MOTOR_PIN, OUTPUT);
	pinMode(ANALOG_PIN, INPUT);
}

void loop()
{
	analogWrite(MOTOR_PIN, analogRead(ANALOG_PIN)/4);
}

