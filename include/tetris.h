#ifndef _TETRIS_H_
#define _TETRIS_H_

#include <memory>
#include <SDL2/SDL.h>
#include <random>
#include "gamestate.h"
#include "grid.h"
#include "tetromino.h"

class Tetris : public GameState {
public:
	Tetris();
	~Tetris();
	void update();
	void render(SDL_Renderer *);
	bool has_ended();
	std::unique_ptr<Tetromino> current_tetromino;
private:
	bool _end;
	std::unique_ptr<Grid> _grid;
	static Uint32 _gravity_callback(Uint32, void*);
	SDL_TimerID _timer;
	std::unique_ptr<Tetromino> _next_tetromino;
	void _swap_pieces();
};

#endif
