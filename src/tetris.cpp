#include <cstdlib>
#include <ctime>
#include "tetris.h"
#include "block.h"
#include "color.h"

Tetris::Tetris() {
	this->_end = false;
	this->_grid = std::unique_ptr<Grid>(new Grid(10, 20, 1));
	this->_timer = SDL_AddTimer(1000, this->_gravity_callback, this);
	srand(time(NULL));
	this->current_tetromino = std::unique_ptr<Tetromino>(Tetromino::new_piece());
	this->_next_tetromino = std::unique_ptr<Tetromino>(Tetromino::new_piece());
	this->_points = 0;
}

Tetris::~Tetris() {

}

void Tetris::update() {
	SDL_Event e;
	while(SDL_PollEvent(&e)) {
		switch(e.type) {
		case SDL_QUIT:
			this->_end = true;
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym) {
			case SDLK_RIGHT:
				this->current_tetromino->
					check_and_move(Right, this->_grid.get());
				break;
			case SDLK_LEFT:
				this->current_tetromino->
					check_and_move(Left, this->_grid.get());
				break;
			case SDLK_DOWN:
				this->current_tetromino->
					check_and_move(Down, this->_grid.get());
				if(this->current_tetromino->must_stop()) {
					this->_swap_pieces();
				}
				break;
			case SDLK_UP:
				this->current_tetromino->rotate(this->_grid.get());
				break;
			case SDLK_SPACE:
				this->_automatic_fall();
			}
		default:
			break;
		}
	}
}

void Tetris::render(SDL_Renderer *renderer) {
	this->_grid->render(renderer);
	this->current_tetromino->render(renderer, this->_grid.get());
}

bool Tetris::has_ended() {
	return this->_end;
}

void Tetris::_swap_pieces() {
	this->_grid->fix_piece(*this->current_tetromino);
	this->current_tetromino.swap(this->_next_tetromino);
	if(!this->_grid->can_move(*this->current_tetromino, Down))
		this->_end = true;
	this->_points += this->_grid->check_tetris();
	printf("Total current points: %d\n", this->_points);
	this->_next_tetromino = std::unique_ptr<Tetromino>(Tetromino::new_piece());
}

void Tetris::_automatic_fall() {
	while(this->current_tetromino->check_and_move(Down, this->_grid.get()));
	this->_swap_pieces();
}

// TODO: Pass only needed parameters, not whole Tetris *
Uint32 Tetris::_gravity_callback(Uint32 interval, void *param) {
	auto t = (Tetris *) param;
	t->current_tetromino->check_and_move(Down, t->_grid.get());
	if(t->current_tetromino->must_stop()) {
		t->_swap_pieces();
	}

	return interval;
}
