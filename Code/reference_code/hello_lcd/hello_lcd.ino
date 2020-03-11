//Hello LCD.ino
#include <LiquidCrystal.h>
int timeSec = 0;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); // Those are the pins for RS, EN, DB4, DB5, DB6, DB7


void setup() {
  // put your setup code here, to run once:

  lcd.begin(16, 2); //Initializes the lcd
  lcd.setCursor(0,0); //sets pos to print to, 0,0 is the very top left. (Column[0-15], row[0-1])
  lcd.print("hello, world!");
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,1);
  lcd.print(timeSec);
  delay(1000); //delay in milliseconds; 1000 ms = 1 s
  timeSec++; //increments it by 1 for each second that passes 
}
