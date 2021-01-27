#ifndef _COLOR_H_
#define _COLOR_H_

#include <cstdint>

class Color {
public:
	Color();
	Color(uint8_t, uint8_t, uint8_t, uint8_t);
	~Color();
	uint8_t r, g, b, a;
};

#endif
