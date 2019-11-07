# PID_GameBoy
Bob and Liam's PID Box in the form of a GameBoy!
- [Planning](https://github.com/lschenc41/PID_GameBoy/blob/master/README.md#planning)
  - [Description](https://github.com/lschenc41/PID_GameBoy/blob/master/README.md#description)
  - [Criteria](https://github.com/lschenc41/PID_GameBoy/blob/master/README.md#criteria)
  - [Constraints](https://github.com/lschenc41/PID_GameBoy/blob/master/README.md#constraints)
  - [Possible Solutions](https://github.com/lschenc41/PID_GameBoy/blob/master/README.md#possible-solutions)
  - [Sketches](https://github.com/lschenc41/PID_GameBoy/blob/master/README.md#sketches)
  - [List of Materials](https://github.com/lschenc41/PID_GameBoy/blob/master/README.md#list-of-materials)
  - [Schedule](https://github.com/lschenc41/PID_GameBoy/blob/master/README.md#schedule)
- [Documentation](https://github.com/lschenc41/PID_GameBoy/blob/master/README.md#documentation)
  
## Planning
### Description
Our initial plan for our PID box is to make it in the shape of a Nintendo Gameboy, and model the design after it. The dimensions will be the same as the Gameboy but with twice (thrice if needed) the depth to make room for the Arduino + backpack, breadboard, LCD + backpack, motor, and battery pack. As our LCD screen doesn’t have the same proportions as the Gameboy screen, we’ll put it at the bottom half of the Gameboy screen and have the rest be made of clear acrylic to see the wheel inside the box, which will poke out of the left side. We’ll also replace all of the original Gameboy controls with our own: the power switch will still be a power switch, the battery light will be our power indicator, the D-Pad will be the potentiometer, the A and B keys will be buttons to adjust the brightness of the screen, the start button will be the PID enable switch, and the select button will turn on the LED behind the wheel.
### Criteria
- LCD screen to display RPM and other info
- Power switch & indicator
- PID enable switch
- Potentiometer to control the wheel
- Wheel connected to motor that breaks a photo interrupter beam
- LED that blinks when the photo interrupter beam is broken
- PID feedback system that corrects errors
- Documentation with:
  - Materials used
  - SolidWorks renderings
  - Actual photos and/or video (well lit and in focus)
  - Fritzing diagram of our circuit
  - Commented code
  - Description of the planning that went into the project, design decisions, and engineering details
  - A schedule of how you spent your time
  - Discussion of problems, errors, miscalculations, and missteps and how we overcame them
### Constraints
1. We realized that it might be difficult or even impossible to keep the size & proportions of an actual Gameboy and fit everything (arduino, motor, lcd, wheel, etc) inside the box.
2. We also realized that our LCD screen is nowhere near the Gameboy’s screen in terms of proportions; our screen is about half the height and is slightly longer.
### Possible Solutions
1. We could solve this by keeping the length and width dimensions and proportions, but double the depth. This would keep it a similar overall size to a Gameboy, and while it would be noticeably thicker, it wouldn’t be too big and would still be recognizable as a Gameboy.
2. To solve this, we decided to have the top half of the Gameboy screen as clear acrylic on our box, and the bottom half as the LCD screen without the sides showing. This acts as a window where you can see the wheel spinning, and there will be an LED behind the clear acrylic that acts as both a backlight and the LED that blinks when the wheel breaks the photointerrupter beam.
### Sketches
<img src="https://github.com/lschenc41/PID_GameBoy/blob/master/PID_Gameboy_Image.PNG" alt="PID_Gameboy_Image" width="200" height="333"> <img src="https://github.com/lschenc41/PID_GameBoy/blob/master/PID_Gameboy_Sketch.PNG" alt="PID_Gameboy_Sketch" width="500" height="250">
### List of Materials
- Arduino
- Breadboard
- Motor
- LED x3
- Switches x3
- Wires 
- Resistors
- Acrylic
- #4-40 socket head screws and nuts
- T-Slots
- Battery
- Battery holder
- LCD screen & backpack
### Schedule
Nov 1: Planning done & submitted
Nov 8: Basic CAD outline completed
Nov 15: T-slots, holes for switches and buttons, and individual parts (wheel) completed
Nov 22: Screen assembly completed
Nov 26: CAD done
\*Nov 27 - Dec 1: Thanksgiving Break
Dec 6: Wiring completed
Dec 13: Code completed
\*Dec 17 - Dec 20: Midterms
\*Dec 23 - Jan 5: Winter Break
Jan 10: Assembly finished
Jan 17: Project done & submitted
 
Essentially, the planning will be done by the end of the first week, the CAD will be done by Thanksgiving break, the code will be done by midterms, and the project will be submitted by two weeks after we return from winter break. We’ll be printing during the same time we work on code to use time efficiently. Overall, this project will take 1 weeks; however, there will be multiple days off as well as Thanksgiving break, winter break, and exams, bringing it closer to a 9 week long project in terms of class time spent working. We tried to work around the long breaks by deciding on finishing something before them, meaning it’s possible that we’ll finish CAD a week before Thanksgiving break, for example.
## Documentation
