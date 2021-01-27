#include "color.h"

Color::Color() {
	// set default constructor to opaque black
	this->r = this->g = this->b = 0;
	this->a = 255;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color::~Color() {

}
