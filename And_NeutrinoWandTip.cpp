
#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include <And_RGBLed.h>
#include "And_NeutrinoWandTip.h"

And_NeutrinoWandTip::And_NeutrinoWandTip(And_RGBLed tipLight, Adafruit_NeoPixel jewel)
{
	_jewel = jewel;
	_tipLight = tipLight;
}
