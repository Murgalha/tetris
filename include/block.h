#ifndef _BLOCK_H_
#define _BLOCK_H_

class Block;

#include <SDL2/SDL.h>
#include <utility>
#include "grid.h"
#include "block.h"
#include "color.h"

class Block {
public:
	Block();
	Block(int8_t, int8_t, Color, int);
	~Block();
	void render(SDL_Renderer *, Grid *);
	void move_down();
	void move_right();
	void move_left();
	void new_position(int8_t, int8_t);
	std::pair<int8_t, int8_t> position();
private:
	std::pair<int8_t, int8_t> _position;
	Color _color;
	int _size;
};

#endif
