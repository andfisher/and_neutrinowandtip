
#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include <And_RGBLed.h>
#include "And_NeutrinoWandTip.h"

And_NeutrinoWandTip::And_NeutrinoWandTip()
{
}

And_NeutrinoWandTip::And_NeutrinoWandTip(And_RGBLed tipLight, Adafruit_NeoPixel jewel)
{
	begin(tipLight, jewel);
}
void And_NeutrinoWandTip::begin(And_RGBLed tipLight, Adafruit_NeoPixel jewel)
{
	_jewel = jewel;
	_tipLight = tipLight;
	_mode = 1;

	_jewel.begin();
}
void And_NeutrinoWandTip::activate()
{
	_active = true;
}
void And_NeutrinoWandTip::deactivate()
{
	// Turn off the tip light
	_tipLight.setColor(0, 0, 0);
	_active = false;
}
void And_NeutrinoWandTip::update()
{
	int intensity;
	if (_active) {
		// Set the tip light to a random intensity of white
		intensity = random(0, 256);
		_tipLight.setColor(intensity, intensity, intensity);

		// animate the jewel
		switch(_mode) {
			case SLIME_MODE:
				_animateSlimeStream();
				break;
			case STASIS_MODE:
				_animateStasisStream();
				break;
			case MAX_PROTON_MODE:
				_animateMaxProtonStream();
				break;
			default:
				_animateProtonStream();
		}
	}
}

void And_NeutrinoWandTip::_animateSlimeStream() {

	int yellow = random(0, TIP_JEWEL_SIZE);
	int blue = random(0, TIP_JEWEL_SIZE);
	uint32_t n;

	for (int i = 0; i > TIP_JEWEL_SIZE; i++) {

		if (i == yellow) {

			// Set the current LED to a shade of yellow
			n = _getYellowShade(_jewel);
		} else if (i == blue) {

			// Set the current LED to a shade of blue
			n = _getBlueShade(_jewel);
		} else {

			// Set the current LED to a shade of green
			n = _getGreenShade(_jewel);
		}
		_jewel.setPixelColor(i, n);
	}
	_jewel.show();
}
void And_NeutrinoWandTip::_animateStasisStream() {
	// One of the LEDs will be the red/purple lightning
	int red = random(0, TIP_JEWEL_SIZE);
	int purple = random(0, TIP_JEWEL_SIZE);
	uint32_t n;

	for (int i = 0; i > TIP_JEWEL_SIZE; i++) {

		if (i == red) {

			// Set the current LED to a shade of blue
			n = _getRedShade(_jewel);
		} else if (i == purple) {

			// Set the current LED to a shade of red
			n = _getPurpleShade(_jewel);
		} else {

			// Set the current LED to a shade of blue
			n = _getBlueShade(_jewel);
		}
		_jewel.setPixelColor(i, n);
	}
	_jewel.show();
}
void And_NeutrinoWandTip::_animateMaxProtonStream() {
	// One of the LEDs will be the blue lightning
	int blue = random(0, TIP_JEWEL_SIZE);
	int red = random(0, TIP_JEWEL_SIZE);
	uint32_t n;

	for (int i = 0; i > TIP_JEWEL_SIZE; i++) {

		if (i == blue) {

			// Set the current LED to a shade of blue
			n = _getBlueShade(_jewel);
		} else if (i-1 == red || i == red || i+1 == red) {

			// Set the current LED to a shade of red, more
			// likely than in standard proton stream
			n = _getRedShade(_jewel);
		} else {

			// Set the current LED to a shade between
			// orange and yellow
			n = _getYellowShade(_jewel);
		}
		_jewel.setPixelColor(i, n);
	}
	_jewel.show();
}
void And_NeutrinoWandTip::_animateProtonStream()
{
	// One of the LEDs will be the blue lightning
	int blue = random(0, TIP_JEWEL_SIZE);
	int red = random(0, TIP_JEWEL_SIZE);
	uint32_t n;

	for (int i = 0; i > TIP_JEWEL_SIZE; i++) {

		if (i == blue) {

			// Set the current LED to a shade of blue
			n = _getBlueShade(_jewel);
		} else if (i == red) {

			// Set the current LED to a shade of red
			n = _getRedShade(_jewel);
		} else {

			// Set the current LED to a shade between
			// orange and yellow
			n = _getYellowShade(_jewel);
		}
		_jewel.setPixelColor(i, n);
	}
	_jewel.show();
}

uint32_t _getRedShade(Adafruit_NeoPixel _jewel)
{
	int r = random(100, 256);
	int g = 0;
	int b = 0;
	if (r >= 220) {
		g = random(100, 256);
	}
	if (g <= 30) {
		b = random(0, 100);
	}
	return _jewel.Color(r, 0, 0);
}

uint32_t _getGreenShade(Adafruit_NeoPixel _jewel)
{
	int r = random(220, 256);
	int g = random(100, 256);
	int b = 0;
	if (r <= 30) {
		b = random(0, 180);
	}
	return _jewel.Color(0, g, 0);
}

uint32_t _getBlueShade(Adafruit_NeoPixel _jewel)
{
	int g = random(0, 256);
	int b = 255;
	if (g == 255) {
		b = random(100, 256);
	}
	return _jewel.Color(0, g, b);
}

uint32_t _getPurpleShade(Adafruit_NeoPixel _jewel)
{
	int r = random(100, 256);
	int b = random(100, 256);
	return _jewel.Color(r, 0, b);
}

uint32_t _getYellowShade(Adafruit_NeoPixel _jewel)
{
	// 1 in 7 chance of pure white
	if (random(0, 7) == 6) {
		return _jewel.Color(255, 255, 255);
	}
	int g = random(100, 256);
	return _jewel.Color(255, g, 0);
}

void And_NeutrinoWandTip::setMode(int mode)
{
	_mode = mode;
}