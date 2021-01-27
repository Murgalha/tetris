#include "grid.h"
#include "utils.h"

Grid::Grid(uint8_t w, uint8_t h, uint8_t b) {
	this->_width = w;
	this->_height = h;
	this->_border = b;
}

Grid::~Grid() {

}

std::pair<int, int> Grid::to_pixels(uint8_t x, uint8_t y) const {
	return std::make_pair(this->to_pixels_x(x), this->to_pixels_y(y));
}

int Grid::to_pixels_x(uint8_t x) const {
	int w_step = WINDOW_WIDTH / (this->_width + 2*this->_border);
	return w_step * x;
}

int Grid::to_pixels_y(uint8_t y) const {
	int h_step = WINDOW_HEIGHT / (this->_height + 2*this->_border);
	return h_step * y;
}

uint8_t Grid::width() const {
	return this->_width;
}

uint8_t Grid::height() const {
	return this->_height;
}

uint8_t Grid::border() const {
	return this->_border;
}
