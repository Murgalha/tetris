#include "tetromino.h"
#include <algorithm>
#include <cstdio>

Tetromino::Tetromino() {

}

Tetromino::Tetromino(TetrominoShape shape) {
	auto pos = POSITIONS[shape];
	auto color = Tetromino::gen_color(shape);
	uint8_t min_x = 255, max_y = 0, max_x = 0;

	for(auto p : pos) {
		this->_blocks.push_back(Block(p.first, p.second, color, 28));
		if(p.first < min_x) {
			min_x = p.first;
		}
		else if(p.first > max_x) {
			max_x = p.first;
		}
		if(p.second > max_y) {
			max_y = p.second;
		}
	}
	this->_color = color;
	this->_rightmost_position = max_x;
	this->_leftmost_position = min_x;
	this->_downmost_position = max_y;
}

Tetromino::~Tetromino() {

}

void Tetromino::render(SDL_Renderer *renderer, Grid *grid) {
	for(auto block : this->_blocks) {
		block.render(renderer, grid);
	}
}

void Tetromino::check_and_move(Direction d, Grid *g) {
	if(this->_can_move(d, g)) {
		this->_move(d);
	}
}

void Tetromino::_move(Direction d) {
	switch(d) {
	case Right:
		this->_move_right();
		break;
	case Left:
		this->_move_left();
		break;
	case Down:
		this->_move_down();
		break;
	default:
		break;
	}
}

bool Tetromino::_can_move(Direction d, Grid *g) {
	// check if piece can move on given direction,
	// inside given grid
	switch(d) {
	case Right:
		return this->_rightmost_position < g->width();
	case Left:
		return this->_leftmost_position > g->border();
	case Down:
		return this->_downmost_position < g->height();
	default:
		return false;
	}
}

void Tetromino::_move_left() {
	for(int i = 0; i < this->_blocks.size(); i++) {
		this->_blocks[i].move_left();
	}
	this->_rightmost_position--;
	this->_leftmost_position--;
}

void Tetromino::_move_right() {
	for(int i = 0; i < this->_blocks.size(); i++) {
		this->_blocks[i].move_right();
	}
	this->_rightmost_position++;
	this->_leftmost_position++;
}

void Tetromino::_move_down() {
	for(int i = 0; i < this->_blocks.size(); i++) {
		this->_blocks[i].move_down();
	}
	this->_downmost_position++;
}

Color Tetromino::gen_color(TetrominoShape shape) {
	switch(shape) {
	case I:
		return CYAN;
	case J:
		return BLUE;
	case L:
		return ORANGE;
	case O:
		return YELLOW;
	case S:
		return GREEN;
	case T:
		return PURPLE;
	case Z:
		return RED;
	default:
		return WHITE;
	}
}
