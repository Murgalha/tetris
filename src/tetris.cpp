#include "tetris.h"
#include "block.h"
#include "color.h"

Tetris::Tetris() {
	this->_end = false;
	this->_grid = std::unique_ptr<Grid>(new Grid(10, 20, 1));
}

Tetris::~Tetris() {

}

void Tetris::update() {
	SDL_Event e;
	while(SDL_PollEvent(&e)) {
		switch(e.type) {
		case SDL_QUIT:
			this->_end = true;
		default:
			break;
		}
	}
}

void Tetris::render(SDL_Renderer *renderer) {
	this->_draw_border(renderer);
}

bool Tetris::has_ended() {
	return this->_end;
}

void Tetris::_draw_border(SDL_Renderer *renderer) {
	Color c(100, 100, 100, 255);
	Block b(0, 0, c, 28);
	Block b2(0, this->_grid->height()+this->_grid->border(), c, 28);

	auto width = this->_grid->width() + 2*this->_grid->border();
	for(int i = 0; i < width; i++) {
		b.render(renderer, this->_grid.get());
		b.move_right();
		b2.render(renderer, this->_grid.get());
		b2.move_right();
	}

	b.new_position(0, 1);
	b2.new_position(this->_grid->width() + this->_grid->border(), 1);
	auto height = this->_grid->height() + 2*this->_grid->border();
	for(int i = 1; i < height - 1; i++) {
		b.render(renderer, this->_grid.get());
		b.move_down();
		b2.render(renderer, this->_grid.get());
		b2.move_down();
	}
}
