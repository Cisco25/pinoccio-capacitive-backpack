#include <SPI.h>
#include <Wire.h>
#include <Scout.h>
#include <GS.h>
#include <bitlash.h>
#include <lwm.h>
#include <js0n.h>

/** Capacitive Sense Library **/
/** http://playground.arduino.cc/Main/CapacitiveSensor?from=Main.CapSense **/
#include <CapacitiveSensor.h>

/** Creation of touch objects **/
CapacitiveSensor   cap_P = CapacitiveSensor(0, 0);
CapacitiveSensor   cap_I = CapacitiveSensor(0, 0);
CapacitiveSensor   cap_N = CapacitiveSensor(0, 0);
CapacitiveSensor   cap_O = CapacitiveSensor(0, 0);

long total_P, total_I, total_N, total_O;

void setup() {
   Scout.setup();
   
   /** Configure send and receive pins **/
   /** CapacitiveSensor(sendPin, receivePin) **/
   cap_P = CapacitiveSensor(8, A3);
   cap_P.set_CS_AutocaL_Millis(0xFFFFFFFF);  // Turn off autocalibrate
   cap_P.set_CS_Timeout_Millis(100);         // Set Timeout to 100 ms
   
   cap_I = CapacitiveSensor(8, A6);
   cap_I.set_CS_AutocaL_Millis(0xFFFFFFFF);  // Turn off autocalibrate
   cap_I.set_CS_Timeout_Millis(100);         // Set Timeout to 100 ms
   
   cap_N = CapacitiveSensor(8, A4);
   cap_N.set_CS_AutocaL_Millis(0xFFFFFFFF);  // Turn off autocalibrate
   cap_N.set_CS_Timeout_Millis(100);         // Set Timeout to 100 ms
   
   cap_O = CapacitiveSensor(8, A5);
   cap_O.set_CS_AutocaL_Millis(0xFFFFFFFF);  // Turn off autocalibrate
   cap_O.set_CS_Timeout_Millis(100);         // Set Timeout to 100 ms
}

void loop() {
    Scout.loop();
    
    /** Read capacitive electrodes **/
    /** capacitiveSensor(numberOfSamples) **/
    total_P =  cap_P.capacitiveSensor(5);
    delay(2);
    total_I =  cap_I.capacitiveSensor(5);
    delay(2);
    total_N =  cap_N.capacitiveSensor(5);
    delay(2);
    total_O =  cap_O.capacitiveSensor(5);
    delay(2);
    
    /** Print measured values and turn on RGB led **/
    if(total_P > 10) {
      RgbLed.red();             // Red
      Serial.print("P\t");
      Serial.println(total_P);  // Print sensor output
    }
    else if(total_I > 10) {
      RgbLed.green();           // Green
      Serial.print("I\t");
      Serial.println(total_I);  // Print sensor output
    }
    else if(total_N > 10) {
      RgbLed.blue();            // Blue
      Serial.print("N\t");
      Serial.println(total_N);  // Print sensor output
    }
    else if(total_O > 10) {
      RgbLed.white();           // White
      Serial.print("O\t");
      Serial.println(total_O);  // Print sensor output
    }
    else RgbLed.turnOff();
    
    delay(10);
}
