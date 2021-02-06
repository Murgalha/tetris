#include "block.h"

Block::Block() {
	this->_position = std::make_pair(0, 0);
	this->_color;
	this->_size = 0;
}

Block::Block(int8_t x, int8_t y, Color c, int s) {
	this->_position = std::make_pair(x, y);
	this->_color = c;
	this->_size = s;
}

Block::~Block() {

}

std::pair<int8_t, int8_t> Block::position() {
	return this->_position;
}

void Block::render(SDL_Renderer *renderer, Grid *grid) {
	auto pos = this->_position;
	auto pixels = grid->to_pixels(pos.first, pos.second);
	Color old_color;

	SDL_GetRenderDrawColor(renderer,
                           &old_color.r,
                           &old_color.g,
                           &old_color.b,
                           &old_color.a);

	SDL_SetRenderDrawColor(renderer,
						   this->_color.r,
						   this->_color.g,
						   this->_color.b,
						   this->_color.a);

	SDL_Rect r;
	r.x = pixels.first;
	r.y = pixels.second;
	r.w = r.h = this->_size;
	SDL_RenderFillRect(renderer, &r);

	SDL_SetRenderDrawColor(renderer,
                           old_color.r,
                           old_color.g,
                           old_color.b,
                           old_color.a);
}

void Block::move_down() {
	this->_position.second += 1;
}

void Block::move_right() {
	this->_position.first += 1;
}

void Block::move_left() {
	this->_position.first -= 1;
}

void Block::new_position(int8_t x, int8_t y) {
	this->_position = std::make_pair(x, y);
}
