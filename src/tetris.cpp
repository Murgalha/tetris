#include <cstdlib>
#include <cstdio>
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
	// @Hardcode: Make move 'to next' and 'from next' functions
	// to avoid hardcoding the translation

	// @Visual: Translate +2y for I-shape and -1x for O-shape
	// tetrominos so they align with the 'Next' text
	this->_next_tetromino->translate(9, 3);
	this->_create_projection();
	this->_update_projection();
	this->_points = 0;

	TTF_Init();
	this->_font = TTF_OpenFont("./fonts/Hack-Regular.ttf", 16);
	if(!this->_font) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		exit(1);
	}

}

Tetris::~Tetris() {
	TTF_Quit();
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
	this->_next_tetromino->render(renderer, this->_grid.get());
	this->_projection->render(renderer, this->_grid.get(), true);
	this->_render_info(renderer);

}

bool Tetris::has_ended() {
	return this->_end;
}

void Tetris::_swap_pieces() {
	this->_grid->fix_piece(*this->current_tetromino);
	this->current_tetromino.swap(this->_next_tetromino);
	this->current_tetromino->translate(-9, -3);
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
	this->_next_tetromino->translate(9, 3);
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

// @Speed: Avoid creating texture and surface everyframe
// @Hardcode: Make this function receive SDL_Texture and SDL_Rect,
// then draw stuff using arguments, not hardcode as it is
void Tetris::_render_info(SDL_Renderer *renderer) {
	SDL_Color White = {255, 255, 255};
	SDL_Surface *surfaceMessage = NULL;
	SDL_Rect Message_rect;

	// Drawing 'Next'
	surfaceMessage = TTF_RenderText_Solid(this->_font, "Next", White);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	Message_rect.x = INFO_BEGIN_X + 30;
	Message_rect.y = INFO_BEGIN_Y;
	Message_rect.w = 80;
	Message_rect.h = 50;

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);

	// Drawing 'Points'
	surfaceMessage = TTF_RenderText_Solid(this->_font, "Points", White);
	Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	Message_rect.y += 200;
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);

	char points[256];
	snprintf(points, 255, "%d", this->_points);

	// Drawing the actual number of points
	surfaceMessage = TTF_RenderText_Solid(this->_font, points, White);
	Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	Message_rect.y += 50;
	Message_rect.w = 30;
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
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
