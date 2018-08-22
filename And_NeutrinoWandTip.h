
#ifndef And_NeutrinoWandTip_h
#define And_NeutrinoWandTip_h

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "And_RGBLed.h"

class And_NeutrinoWandTip {
	public:
		And_NeutrinoWandTip(And_RGBLed tipLight, Adafruit_NeoPixel jewel);
	private:
		And_RGBLed _tipLight;
		Adafruit_NeoPixel _jewel;
};

#endif