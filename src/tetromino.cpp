#include "tetromino.h"
#include <algorithm>
#include <cstdio>

Tetromino::Tetromino() {
	int random_number = rand() % NSHAPES;
	TetrominoShape shape = (TetrominoShape) random_number;
	this->_set_piece(shape);
}

Tetromino::Tetromino(TetrominoShape shape) {
	this->_set_piece(shape);
}

void Tetromino::_set_piece(TetrominoShape shape) {
	auto pos = POSITIONS[shape];
	this->_must_stop = false;
	this->_shape = shape;

	// Set pivot and color based on shape
	switch(this->_shape) {
	case I:
		this->_pivot = std::make_pair(5, -1);
		this->_color = CYAN;
		break;
	case J:
		this->_pivot = std::make_pair(6, 0);
		this->_color = BLUE;
		break;
	case L:
		this->_pivot = std::make_pair(5, 0);
		this->_color = ORANGE;
		break;
	case O:
		this->_pivot = std::make_pair(6, 0);
		this->_color = YELLOW;
		break;
	case S:
		this->_pivot = std::make_pair(5, 0);
		this->_color = GREEN;
		break;
	case T:
		this->_pivot = std::make_pair(5, -1);
		this->_color = PURPLE;
		break;
	case Z:
		this->_pivot = std::make_pair(5, 0);
		this->_color = RED;
		break;
	default:
		this->_pivot = std::make_pair(0, 0);
		this->_color = WHITE;
		break;
	}


	for(auto p : pos) {
		// insert block on vector
		Block b(p.first, p.second, this->_color, 28);
		this->_blocks.push_back(b);
	}

}

Tetromino::~Tetromino() {

}

void Tetromino::render(SDL_Renderer *renderer, Grid *grid, bool outline) {
	for(auto block : this->_blocks) {
		block.render(renderer, grid, outline);
	}
}

bool Tetromino::maybe_move(Direction d, Grid *g) {
	/*
	  Check if tetromino can move on given direction
	  and move it if possible.
	  Returns true if piece has moved, false otherwise
	 */
	bool can_move = g->can_move(*this, d);
	if(can_move) {
		this->_move(d);
	}
	else {
		// if can't move down, piece should stop falling
		if(d == Down) {
			this->_must_stop = true;
		}
	}
	return can_move;
}

void Tetromino::rotate(Grid *g) {
	if(this->_shape != O) {
		auto possible_new = Tetromino(this->_shape);
		bool can_rotate = true;
		for(int i = 0; i < this->_blocks.size(); i++) {
			auto block_pos = this->_blocks[i].position();
			// move current points to origin base on _pivot
			auto x_old = block_pos.first - this->_pivot.first;
			auto y_old = block_pos.second - this->_pivot.second;
			// set new rotated pieces
			auto x_new = -y_old + this->_pivot.first;
			auto y_new = x_old + this->_pivot.second;
			possible_new.blocks()[i].new_position(x_new, y_new);
		}
		// try to place the piece, then try wall kick right
		// and left
		if(!g->can_move(possible_new, Still)) {
			bool kick_right = possible_new.maybe_move(Right, g);
			bool kick_left = true;
			if(!kick_right) {
				kick_left = possible_new.maybe_move(Left, g);
			}
			if(!kick_left) {
				can_rotate = false;
			}
		}
		if(can_rotate) {
			std::pair<int8_t, int8_t> pos;
			for(int i = 0; i < possible_new.blocks().size(); i++) {
				pos = possible_new.blocks()[i].position();
				this->_blocks[i].new_position(pos.first, pos.second);
			}
		}
	}
}

void Tetromino::_move(Direction d) {
	std::pair<int8_t, int8_t> offset = std::make_pair(0, 0);
	switch(d) {
	case Right:
		offset.first = 1;
		break;
	case Left:
		offset.first = -1;
		break;
	case Down:
		offset.second = 1;
		break;
	default:
		break;
	}
	for(int i = 0; i < this->_blocks.size(); i++)
		this->_blocks[i].translate(offset.first, offset.second);
	this->_pivot.first += offset.first;
	this->_pivot.second += offset.second;
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

TetrominoShape Tetromino::shape() const {
	return this->_shape;
}
