#include "Arduino.h"
	//Define statements basically take the first word/string/thingy (LED_PIN) 
	//and replace every instance of it in your code with the thing after the space
	//just another way of defining certain pins for tasks

#define LED_PIN 5
	//If writing an analog value, the pin MUST have a ~ next to it on the arduino board itself.

int direction; //used for defining whether it's getting brighter or dimmer.

float glow; //how much power to send to the LED. 0 is completely off and 255 is completely on
//NOTE: it starts from 0 to 100, but math adjusts that to 0 to 255 before it's sent to the arduino
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
	if(glow == 100)
	{
		direction = -5;
	}
	analogWrite(LED, glow*255/100); //here's that math taking the place of a map funtion
	glow = glow + direction;
	for(int n = 1; n <= glow/10; n++)
		//This prints a triangle wave of X's to the Serial Monitor
		//The "for" loop prints 'glow' # of spaces
		//And the "Serial.print("X\n");" puts an X at the end of those white spaces to make the wave
		//The "10" in the for loop is just a scalar so that the wave isn't stupid big and makes the arduino lag
		//Just get rid of it and you'll see what I mean
	{
		Serial.print(" ");
	}
	Serial.print("X\n");
	delay(10); //Normal delay to prevent any funny buisiness
}
