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
	this->current_tetromino =
		std::unique_ptr<Tetromino>(new Tetromino);
	this->_next_tetromino =
		std::unique_ptr<Tetromino>(new Tetromino);

	this->_create_projection();
	this->_update_projection();
	this->_points = 0;
}

Tetris::~Tetris() {

}

void Tetris::update() {
	SDL_Event e;
	bool valid_key = false;
	while(SDL_PollEvent(&e)) {
		switch(e.type) {
		case SDL_QUIT:
			this->_end = true;
			break;
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym) {
			case SDLK_RIGHT:
				this->current_tetromino->
					maybe_move(Right, this->_grid.get());
				valid_key = true;
				break;
			case SDLK_LEFT:
				this->current_tetromino->
					maybe_move(Left, this->_grid.get());
				valid_key = true;
				break;
			case SDLK_DOWN:
				this->current_tetromino->
					maybe_move(Down, this->_grid.get());
				valid_key = true;
				break;
			case SDLK_UP:
				this->current_tetromino->rotate(this->_grid.get());
				valid_key = true;
				break;
			case SDLK_SPACE:
				this->_automatic_fall();
				break;
			}
			// only if a valid key is pressed the projection
			// will update
			if(valid_key) {
				this->_update_projection();
			}
			if(this->current_tetromino->must_stop())
				this->_swap_pieces();
			break;
		default:
			break;
		}
	}
}

void Tetris::render(SDL_Renderer *renderer) {
	this->_grid->render(renderer);
	this->current_tetromino->render(renderer, this->_grid.get());
	this->_projection->render(renderer, this->_grid.get(), true);
}

bool Tetris::has_ended() {
	return this->_end;
}

void Tetris::_swap_pieces() {
	this->_grid->fix_piece(*this->current_tetromino);
	this->current_tetromino.swap(this->_next_tetromino);
	// Check end game
	// if newly placed piece cannot move
	if(!this->current_tetromino->maybe_move(Down, this->_grid.get()))
		this->_end = true;
	this->_points += this->_grid->check_tetris();
	printf("Total current points: %d\n", this->_points);
	// on new piece, create and update projection
	this->_create_projection();
	this->_update_projection();
	this->_next_tetromino =
		std::unique_ptr<Tetromino>(new Tetromino);
}

void Tetris::_create_projection() {
	Tetromino *current = this->current_tetromino.get();
	Tetromino *projection = new Tetromino(current->shape());
	this->_projection = std::unique_ptr<Tetromino>(projection);
}

void Tetris::_update_projection() {
	// Set the projection position the same as current block
	// then move down until it cannot anymore
	for(int i = 0; i < this->current_tetromino->blocks().size(); i++) {
		auto pos = this->current_tetromino->blocks()[i].position();
		this->_projection->blocks()[i].new_position(pos.first, pos.second);
	}
	while(this->_projection->maybe_move(Down, this->_grid.get()));
}

void Tetris::_automatic_fall() {
	Grid *g = this->_grid.get();
	while(this->current_tetromino->maybe_move(Down, g));
	this->_swap_pieces();
}

// TODO: Pass only needed parameters, not whole Tetris *
Uint32 Tetris::_gravity_callback(Uint32 interval, void *param) {
	auto t = (Tetris *) param;
	t->current_tetromino->maybe_move(Down, t->_grid.get());
	if(t->current_tetromino->must_stop()) {
		t->_swap_pieces();
	}

	return interval;
}
