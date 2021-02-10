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
	std::unique_ptr<Tetromino> _projection;
	void _update_projection();
	void _create_projection();
	void _swap_pieces();
	void _automatic_fall();
	uint32_t _points;
};

#endif
