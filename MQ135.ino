/* 
 *Connection pins:

Arduino       MQ-135
   A0            A0
 +5V            VCC
 GND            GND
 
*/

#include "MQ135.h"
#include <FastLED.h>
#include <SoftwareSerial.h>

//librerias del ESP WIFI
#include <ESP8266WiFi.h>

//libreria del gps
#include <TinyGPS.h>

TinyGPS gps;
SoftwareSerial softSerial(D6, D5); //(TX, RX)

const int Trigger = D3;   //Pin digital 2 para el Trigger del sensor 0 = d3
const int Echo = D4;   //Pin digital 3 para el Echo del sensor 2 = d4


//leds
#define NUM_LEDS 8
#define DATA_PIN D1 //12 = d6
#define CLOCK_PIN D2 //4 = d2

int analogPin = 0;

// Define the array of leds
CRGB leds[NUM_LEDS];

MQ135 gasSensor = MQ135(analogPin);

#define RZERO 310 // 76.63

int i = 0;

double result;
double rzero;

void setup() {
  Serial.begin(9600);

  FastLED.addLeds<DOTSTAR, DATA_PIN,CLOCK_PIN,BGR >(leds, NUM_LEDS);
}

void loop() {
 if (i==0) {
   rzero = gasSensor.getRZero(); // float
 }
 if (i>0) {  
   result = gasSensor.getRZero();
   rzero = (rzero + result)/2;
  }
  
  float ppm = gasSensor.getPPM();

  if(result <= 955.48 e7  ){
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Yellow;
      FastLED.show();
      delay(50);
    }
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[8 - i] = CRGB::Black;
      FastLED.show();
      delay(50);
    }
  }else{
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Green;
      FastLED.show();
      delay(50);
    }
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[8 - i] = CRGB::Black;
      FastLED.show();
      delay(50);
    }
  }
  
  if(ppm <= 9.46){
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Green;
      FastLED.show();
      delay(50);
    }
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[8 - i] = CRGB::Black;
      FastLED.show();
      delay(50);
    }
  }else{
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Red;
      FastLED.show();
      delay(50);
    }
    for (int i = 0; i <  NUM_LEDS; i++) {
      leds[8 - i] = CRGB::Black;
      FastLED.show();
      delay(50);
    }  
  }
  
  Serial.print(rzero);
  Serial.print(", ");
  Serial.print(result);
  Serial.print(", ");
  Serial.print(ppm);
  Serial.println(" ppm");
  i++;
  delay(200);
}
