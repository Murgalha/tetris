#include "utils.h"
#include "game.h"

Game::Game(GameState *gs) {
	SDL_Window *w = NULL;
	SDL_Renderer *r = NULL;
	int wflags = 0, rflags = 0;

	if(SDL_Init(SDL_INIT_EVERYTHING)) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		exit(1);
	}

	w = SDL_CreateWindow("Tetris",
						 SDL_WINDOWPOS_CENTERED,
						 SDL_WINDOWPOS_CENTERED,
						 WINDOW_WIDTH,
						 WINDOW_HEIGHT,
						 wflags);
	if(!w) {
        SDL_Log("Unable to initialize Window: %s", SDL_GetError());
		exit(1);
	}

	r = SDL_CreateRenderer(w, -1, rflags);
	if(!r) {
        SDL_Log("Unable to initialize renderer: %s", SDL_GetError());
		exit(1);
	}

	this->_window = std::unique_ptr<SDL_Window, SDL_Deleter>(w);
	this->_renderer = std::unique_ptr<SDL_Renderer, SDL_Deleter>(r);
	this->_gs =
		std::unique_ptr<GameState>(gs);
}

Game::~Game() {
	SDL_Quit();
}

void Game::run_loop() {
	while(!this->_gs->has_ended()) {
		this->_update();
		this->_render();
	}
}

void Game::_update() {
	this->_gs->update();
}

void Game::_render() {
	SDL_RenderClear(this->_renderer.get());

	this->_gs->render(this->_renderer.get());

	SDL_RenderPresent(this->_renderer.get());
}
