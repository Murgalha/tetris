#ifndef _GAME_H_
#define _GAME_H_

#include <SDL2/SDL.h>
#include <memory>
#include "sdldestroyer.h"
#include "gamestate.h"


class Game {
public:
	Game(GameState *);
	~Game();
	void run_loop();
private:
	std::unique_ptr<SDL_Window, SDL_Deleter> _window;
	std::unique_ptr<SDL_Renderer, SDL_Deleter> _renderer;
	std::unique_ptr<GameState> _gs;
	void _update();
	void _render();
};

#endif
