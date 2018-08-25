
#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include <And_RGBLed.h>
#include "And_NeutrinoWandTip.h"

And_NeutrinoWandTip::And_NeutrinoWandTip()
{
}

And_NeutrinoWandTip::And_NeutrinoWandTip(And_RGBLed &tipLight, Adafruit_NeoPixel &jewel, int brightness, int delay)
{
	begin(tipLight, jewel, brightness, delay);
}
void And_NeutrinoWandTip::begin(And_RGBLed &tipLight, Adafruit_NeoPixel &jewel, int brightness, int delay)
{
	jewel.begin();

	_jewel = jewel;
	_tipLight = tipLight;
	_mode = 0;
	_delay = delay;

	_jewel.setBrightness(brightness);
	_jewel.show();
}
void And_NeutrinoWandTip::activate()
{
	_active = true;
	_nextUpdate = millis() + _delay;
}
void And_NeutrinoWandTip::deactivate()
{
	// Turn off the tip light
	_tipLight.setColor(0, 0, 0);
	_active = false;
}
void And_NeutrinoWandTip::update(unsigned long ms)
{
	int intensity;

	if (_active) {

		if (ms < _nextUpdate) {
			return;
		}

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

		_nextUpdate = ms + _delay;
	}
}

void And_NeutrinoWandTip::_animateSlimeStream() {

	int yellow = random(0, TIP_JEWEL_SIZE);
	int blue = random(0, TIP_JEWEL_SIZE);
	uint32_t n;

	for (int i = 0; i < TIP_JEWEL_SIZE; i++) {

		if (i == yellow) {

			// Set the current LED to a shade of yellow
			n = _getYellowShade();
		} else if (i == blue) {

			// Set the current LED to a shade of blue
			n = _getBlueShade();
		} else {

			// Set the current LED to a shade of green
			n = _getGreenShade();
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

	for (int i = 0; i < TIP_JEWEL_SIZE; i++) {

		if (i == red) {

			// Set the current LED to a shade of blue
			n = _getRedShade();
		} else if (i == purple) {

			// Set the current LED to a shade of red
			n = _getPurpleShade();
		} else {

			// Set the current LED to a shade of blue
			n = _getBlueShade();
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

	for (int i = 0; i < TIP_JEWEL_SIZE; i++) {

		if (i == blue) {

			// Set the current LED to a shade of blue
			n = _getBlueShade();
		} else if (i-1 == red || i == red || i+1 == red) {

			// Set the current LED to a shade of red, more
			// likely than in standard proton stream
			n = _getYellowShade();
		} else {

			// Set the current LED to a shade between
			// orange and yellow
			n = _getRedShade();
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

	for (int i = 0; i < TIP_JEWEL_SIZE; i++) {

		if (i == blue) {

			// Set the current LED to a shade of blue
			n = _getBlueShade();
		} else if (i == red) {

			// Set the current LED to a shade of red
			n = _getRedShade();
		} else {

			// Set the current LED to a shade between
			// orange and yellow
			n = _getYellowShade();
		}
		_jewel.setPixelColor(i, n);
	}
	_jewel.show();
}

uint32_t And_NeutrinoWandTip::_getRedShade()
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

uint32_t And_NeutrinoWandTip::_getGreenShade()
{
	int r = random(220, 256);
	int g = random(100, 256);
	int b = 0;
	if (r <= 30) {
		b = random(0, 180);
	}
	return _jewel.Color(0, g, 0);
}

uint32_t And_NeutrinoWandTip::_getBlueShade()
{
	int g = random(0, 256);
	int b = 255;
	if (g == 255) {
		b = random(100, 256);
	}
	return _jewel.Color(0, g, b);
}

uint32_t And_NeutrinoWandTip::_getPurpleShade()
{
	int r = random(100, 256);
	int b = random(100, 256);
	return _jewel.Color(r, 0, b);
}

uint32_t And_NeutrinoWandTip::_getYellowShade()
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