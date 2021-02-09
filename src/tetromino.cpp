#include "tetromino.h"
#include <algorithm>
#include <cstdio>

Tetromino::Tetromino() {

}

Tetromino::Tetromino(TetrominoShape shape) {
	auto pos = POSITIONS[shape];
	auto color = Tetromino::gen_color(shape);

	for(auto p : pos) {
		// insert block on vector
		this->_blocks.push_back(Block(p.first, p.second, color, 28));
	}
	this->_color = color;
	this->_must_stop = false;
	this->_shape = shape;
	this->_box_size = Tetromino::gen_box_size(this->_shape);
	this->_update_edges();
	this->_pivot = Tetromino::gen_pivot(this->_shape);
}

Tetromino::~Tetromino() {

}

void Tetromino::render(SDL_Renderer *renderer, Grid *grid) {
	for(auto block : this->_blocks) {
		block.render(renderer, grid);
	}
}

bool Tetromino::check_and_move(Direction d, Grid *g) {
	bool can_move = this->can_move(d, g);
	if(can_move) {
		this->_move(d);
	}
	else {
		if(d == Down) {
			this->_must_stop = true;
		}
	}
	return can_move;
}

void Tetromino::rotate(Grid *g) {
	auto possible_new = Tetromino(this->_shape);
	bool can_rotate = true;

	for(int i = 0; i < this->_blocks.size(); i++) {
		auto block_pos = this->_blocks[i].position();
		auto x_old = block_pos.first - this->_pivot.first;
		auto y_old = block_pos.second - this->_pivot.second;
		auto x_new = -y_old + this->_pivot.first;
		auto y_new = x_old + this->_pivot.second;
		possible_new.blocks()[i].new_position(x_new, y_new);
	}
	if(!possible_new.can_move(Still, g)) {
		if(possible_new.can_move(Right, g)) {
			possible_new.check_and_move(Right, g);
		}
		else if(possible_new.can_move(Left, g)) {
			possible_new.check_and_move(Left, g);
		}
		else {
			can_rotate = false;
		}
	}
	if(can_rotate) {
		std::pair<int8_t, int8_t> pos;
		for(int i = 0; i < possible_new.blocks().size(); i++) {
			pos = possible_new.blocks()[i].position();
			this->_blocks[i].new_position(pos.first, pos.second);
		}
		this->_update_edges();
	}
}

void Tetromino::_update_edges() {
	int8_t min_x = 127, max_y = 0, max_x = 0;
	for(auto block : this->_blocks) {
		auto p = block.position();
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
	this->_rightmost_position = max_x;
	this->_leftmost_position = min_x;
	this->_downmost_position = max_y;
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

bool Tetromino::can_move(Direction d, Grid *g) {
	// check if piece can move on given direction,
	// inside given grid
	printf("Leftmost: %d\n", this->_leftmost_position);
	printf("Rightmost: %d\n", this->_rightmost_position);
	printf("Downmost: %d\n", this->_downmost_position);
	return g->can_move(*this, d);
}

void Tetromino::_move_left() {
	for(int i = 0; i < this->_blocks.size(); i++) {
		this->_blocks[i].move_left();
	}
	this->_rightmost_position--;
	this->_leftmost_position--;
	this->_pivot.first--;
}

void Tetromino::_move_right() {
	for(int i = 0; i < this->_blocks.size(); i++) {
		this->_blocks[i].move_right();
	}
	this->_rightmost_position++;
	this->_leftmost_position++;
	this->_pivot.first++;
}

void Tetromino::_move_down() {
	for(int i = 0; i < this->_blocks.size(); i++) {
		this->_blocks[i].move_down();
	}
	this->_downmost_position++;
	this->_pivot.second++;
}

bool Tetromino::must_stop() {
	return this->_must_stop;
}

std::vector<Block> &Tetromino::blocks() {
	return this->_blocks;
}

Color &Tetromino::color() {
	return this->_color;
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

uint8_t Tetromino::gen_box_size(TetrominoShape shape) {
	switch(shape) {
	case I:
		return 4;
	case J:
	case L:
	case S:
	case T:
	case Z:
		return 3;
	case O:
		return 2;
	default:
		return 0;
	}
}

std::pair<int8_t, int8_t> Tetromino::gen_pivot(TetrominoShape shape) {
	switch(shape) {
	case I:
		return std::make_pair(5, -1);
	case J:
		return std::make_pair(6, 0);
	case L:
		return std::make_pair(5, 0);
	case O:
		return std::make_pair(6, 0);
	case S:
		return std::make_pair(5, 0);
	case T:
		return std::make_pair(5, -1);
	case Z:
		return std::make_pair(5, 0);
	default:
		return std::make_pair(0, 0);
	}
}

Tetromino *Tetromino::new_piece() {
	int random_number = rand() % 7;
	TetrominoShape shape = (TetrominoShape) random_number;
	return new Tetromino(shape);
}
