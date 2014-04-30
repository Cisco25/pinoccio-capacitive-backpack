Pinoccio Capacitive Backpack
============================
Circuit, code and information for the Pinoccio capacitive backpack

To view layout and order this backpack from OSH Park: http://oshpark.com/shared_projects/NBBgAHbW

To get started with P-I-N-O capacitive touches:
- Jump 4x resistors footprints R2 to R5
- Solder 4x 1MOhm resistors 0603 size onto C2 to C5 footprints
- Download and install ArduinoCapSense library: http://playground.arduino.cc/Main/CapacitiveSensor?from=Main.CapSense
- Plug backpack and upload sketch CapTouch_PINO to scout using Arduino IDE (nightly build recommended by Pinoccio)
- Press one of the capacitive touch P, I, N or O: RGB led lights up with different colors!

To get started with Slider:
- Jump 3x resistors footprints R7 to R9
- Solder 3x 1MOhm resistors 0603 size onto C7 to C9 footprints
- Download and install ArduinoCapSense library: http://playground.arduino.cc/Main/CapacitiveSensor?from=Main.CapSense
- Plug backpack and upload sketch CapTouch to scout using Arduino IDE (nightly build recommended by Pinoccio)
- Slowly move finger up and down on slider while pressing one of the capacitive touch P, I, N or O: RGB led flashing speed changes!
