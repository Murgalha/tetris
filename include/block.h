#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <SDL2/SDL.h>
#include <utility>
#include "grid.h"
#include "block.h"
#include "color.h"

class Block {
public:
	Block();
	Block(uint8_t, uint8_t, Color, int);
	~Block();
	void render(SDL_Renderer *, Grid *);
	void move_down();
	void move_right();
	void move_left();
	void new_position(uint8_t, uint8_t);
	std::pair<uint8_t, uint8_t> position();
private:
	std::pair<uint8_t, uint8_t> _position;
	Color _color;
	int _size;
};

#endif
