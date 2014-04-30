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

CapacitiveSensor   cap_S0 = CapacitiveSensor(0, 0);
CapacitiveSensor   cap_S1 = CapacitiveSensor(0, 0);
CapacitiveSensor   cap_S2 = CapacitiveSensor(0, 0);

long total_P, total_I, total_N, total_O, total_S0, total_S1, total_S2;
unsigned int sliderState = 0x00;
unsigned int sliderNextState = 0x00;
unsigned int ms = 12;

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
   
   cap_S0 = CapacitiveSensor(2, A0);
   cap_S0.set_CS_AutocaL_Millis(0xFFFFFFFF);  // Turn off autocalibrate
   cap_S0.set_CS_Timeout_Millis(100);         // Set Timeout to 100 ms
   
   cap_S1 = CapacitiveSensor(2, A1);
   cap_S1.set_CS_AutocaL_Millis(0xFFFFFFFF);  // Turn off autocalibrate
   cap_S1.set_CS_Timeout_Millis(100);         // Set Timeout to 100 ms
   
   cap_S2 = CapacitiveSensor(2, A2);
   cap_S2.set_CS_AutocaL_Millis(0xFFFFFFFF);  // Turn off autocalibrate
   cap_S2.set_CS_Timeout_Millis(100);         // Set Timeout to 100 ms
}

void loop() {
    Scout.loop();
    
    /** Read capacitive electrodes **/
    /** capacitiveSensor(numberOfSamples) **/
    total_P =  cap_P.capacitiveSensor(5);
    //delay(2);
    total_I =  cap_I.capacitiveSensor(5);
    //delay(2);
    total_N =  cap_N.capacitiveSensor(5);
    //delay(2);
    total_O =  cap_O.capacitiveSensor(5);
    //delay(2);
    total_S0 =  cap_S0.capacitiveSensor(5);
    //delay(2);
    total_S1 =  cap_S1.capacitiveSensor(5);
    //delay(2);
    total_S2 =  cap_S2.capacitiveSensor(5);
    //delay(2);
    
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
    
    if((total_S0 > 10)||(total_S1 > 10)||(total_S2 > 10)) {       // Slider touch detected
      
      if((total_S0 > 10)&&(total_S1 < 10)&&(total_S2 > 10))       // S0 and S2
        sliderNextState = 0x80|0x02;
      else if((total_S0 < 10)&&(total_S1 < 10)&&(total_S2 > 10))  // S2 only
        sliderNextState = 0x80|0x04;
      else if((total_S0 < 10)&&(total_S1 > 10)&&(total_S2 > 10))  // S2 and S1
        sliderNextState = 0x80|0x08;  
      else if((total_S0 < 10)&&(total_S1 > 10)&&(total_S2 < 10))  // S1 only
        sliderNextState = 0x80|0x10;
      else if((total_S0 > 10)&&(total_S1 > 10)&&(total_S2 < 10))  // S1 and S0
        sliderNextState = 0x80|0x20; 
      else if((total_S0 > 10)&&(total_S1 < 10)&&(total_S2 < 10)) { // S0 only
      
          if(sliderState == (0x80|0x02))        // Finger was on S0 and S2
            sliderNextState = 0x80|0x01;        // Finger is on S0-BOTTOM
          else if(sliderState == (0x80|0x20))   // Finger was on S1 and S0
            sliderNextState = 0x80|0x40;        // Finger is on S0-TOP
          else if(sliderState == 0x00)          // First touch is on S0 only
            sliderNextState = 0xFF;             // Not possible to locate finger!
      } else
        sliderNextState = 0xFF;    // Error: no touch (bad detection)
    
      if(sliderNextState!=0xFF) {         // No error: update current state
        sliderState = sliderNextState;
        Serial.println(sliderState, BIN);
      } else {                            // Error detected
        Serial.println("Touch error");
      }
    } else {  // No touch detected: reset slider state
      sliderState = 0x00;
      sliderNextState = 0x00;
    }
    
    if(sliderState!=0) {
      switch(sliderState&0x7F) {
        case(0x01):
          if(ms > 4)    // Decrease loop time by 2*4ms
            ms = ms - 4;
          else
            ms = 4;
          break;
        case(0x02):
          if(ms > 4)    // Decrease loop time by 2*2ms
            ms = ms - 2;
          else
            ms = 4;
          break;
        case(0x04):
          if(ms > 4)    // Decrease loop time by 2*1ms
            ms = ms - 1;
          else
            ms = 4;
          break;
         case(0x10):
          if(ms < 100)  // Increase loop time by 2*1ms
            ms = ms + 1;
          else
            ms = 100;
          break;
        case(0x20):
          if(ms < 100)  // Increase loop time by 2*2ms
            ms = ms + 2;
          else
            ms = 100;
          break;
        case(0x40):
          if(ms < 100)  // Increase loop time by 2*4ms
            ms = ms + 4;
          else
            ms = 100;
          break;
      }
      Serial.print("ms\t");
      Serial.println(ms);
    }
      
    delay(ms);
    RgbLed.turnOff();
    delay(ms);
}
