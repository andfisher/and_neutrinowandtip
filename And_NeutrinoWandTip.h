
#ifndef And_NeutrinoWandTip_h
#define And_NeutrinoWandTip_h

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "And_RGBLed.h"

/**
   Pack Modes, inspired by the Video Game:
   Default (Proton) stream, Stasis stream, Slime blower
   and Maximum Proton stream (use for crossing the
   streams?)
*/
#define PROTON_MODE 0
#define SLIME_MODE 1
#define STASIS_MODE 2
#define MAX_PROTON_MODE 3

#define TIP_JEWEL_SIZE 7

class And_NeutrinoWandTip {
	public:
		And_NeutrinoWandTip(And_RGBLed tipLight, Adafruit_NeoPixel jewel);
		And_NeutrinoWandTip(void);
		void begin(And_RGBLed tipLight, Adafruit_NeoPixel jewel);
		void activate();
		void deactivate();
		void update();
		void setMode(int mode);
	private:
		And_RGBLed _tipLight;
		Adafruit_NeoPixel _jewel;
		int _mode;
		bool _active;
		void _animateProtonStream();
		void _animateSlimeStream();
		void _animateStasisStream();
		void _animateMaxProtonStream();

		uint32_t _getRedShade(Adafruit_NeoPixel _jewel);
		uint32_t _getGreenShade(Adafruit_NeoPixel _jewel);
		uint32_t _getBlueShade(Adafruit_NeoPixel _jewel);
		uint32_t _getPurpleShade(Adafruit_NeoPixel _jewel);
		uint32_t _getYellowShade(Adafruit_NeoPixel _jewel);
};
typedef And_NeutrinoWandTip And_NeutrinoWandTip;

#endif