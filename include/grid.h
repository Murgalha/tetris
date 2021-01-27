#ifndef _GRID_H_
#define _GRID_H_

#include <cstdint>
#include <utility>

class Grid {
public:
	Grid(uint8_t, uint8_t, uint8_t);
	~Grid();
	std::pair<int, int> to_pixels(uint8_t, uint8_t) const;
	int to_pixels_x(uint8_t) const;
	int to_pixels_y(uint8_t) const;
	uint8_t width() const;
	uint8_t height() const;
	uint8_t border() const;
private:
	uint8_t _width, _height, _border;
};

#endif
