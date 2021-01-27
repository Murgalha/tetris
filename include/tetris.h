#ifndef _TETRIS_H_
#define _TETRIS_H_

#include <memory>
#include <SDL2/SDL.h>
#include "gamestate.h"
#include "grid.h"

class Tetris : public GameState {
public:
	Tetris();
	~Tetris();
	void update();
	void render(SDL_Renderer *);
	bool has_ended();
private:
	bool _end;
	std::unique_ptr<Grid> _grid;
	void _draw_border(SDL_Renderer *);
};

#endif
