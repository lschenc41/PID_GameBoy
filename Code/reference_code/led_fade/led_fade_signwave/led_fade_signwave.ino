#include "Arduino.h"

#define LED_PIN 5
	//If writing an analog value, the pin MUST have a ~ next to it on the arduino board itself.
	//Define statements basically take the first word/string/thingy (LED_PIN) 
	//and replace every instance of it in your code with the thing after the space
	//just another way of defining certain pins for tasks

int direction; //used for defining whether it's getting brighter or dimmer.

float glow; //how much power to send to the LED. 0 is completely off and 255 is completely on

void setup() {
		// the setup function runs once when you press reset or power the board
	Serial.begin(9600);
		//If your printing to the Serial Monitor, you'll need this
	pinMode(LED_PIN, OUTPUT);
	glow = 0;

	direction = 5; 
		//If positive #, the number is increasing. If negative #, the number is decreasing.
		//The starting number probably isn't necessary, but it's better to have it then not
}

// the loop function runs over and over again forever
void loop() {
	if(glow == 0)
	{
		direction = 5;
	}
	if(glow == 315) //it's 315 here because it's an appoximate of pi that's an integer and is a multiple of the int direction
		//it gets divided later into a domain of approx 0 to pi/2
		//this domain corresponds to the /\ of a sin wave instead of a comple period which dips negative
	{
		direction = -5;
	}
	analogWrite(LED, 255*sin(glow/200));
		//that scalar (255 in this case) determines the domain of the possible values sent to the function (from 0 to said scalar)
	glow = glow + direction;
	for(int n = 1; n <= 50*sin(glow/200); n++)
		//it's 50 here because printing 255 spaces is a bad idea
	{
		Serial.print(" ");
	}
	Serial.print("X\n");
	delay(10);
	delay(500-glow);
}
