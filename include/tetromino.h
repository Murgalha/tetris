#ifndef _TETROMINO_H_
#define _TETROMINO_H_

#include <memory>
#include <vector>
#include <utility>
#include "block.h"
#include "color.h"
#include "utils.h"

typedef enum {
	I = 0,
	J,
	L,
	O,
	S,
	T,
	Z
} TetrominoShape;

class Tetromino {
public:
	Tetromino(TetrominoShape);
	Tetromino();
	~Tetromino();
	void render(SDL_Renderer *, Grid *);
	void check_and_move(Direction, Grid *);
	static Color gen_color(TetrominoShape);
	static std::vector<Block> gen_blocks(TetrominoShape);
private:
	void _move(Direction);
	void _move_down();
	void _move_left();
	void _move_right();
	bool _can_move(Direction, Grid *);
	std::vector<Block> _blocks;
	uint8_t _rightmost_position;
	uint8_t _leftmost_position;
	uint8_t _downmost_position;
	Color _color;
};

const Color CYAN = Color(0, 255, 255, 255);
const Color BLUE = Color(0, 0, 255, 255);
const Color ORANGE = Color(255, 165, 0, 255);
const Color YELLOW = Color(255, 255, 0, 255);
const Color GREEN = Color(0, 255, 0, 255);
const Color PURPLE = Color(128, 0, 128, 255);
const Color RED = Color(255, 0, 0, 255);
const Color BLACK = Color(0, 0, 0, 255);
const Color WHITE = Color(255, 255, 255, 255);
const Color GREY = Color(120, 120, 120, 255);

const std::vector< std::vector< std::pair<uint8_t, uint8_t> > > POSITIONS {
	{
		std::make_pair(4, 0),
		std::make_pair(5, 0),
		std::make_pair(6, 0),
		std::make_pair(7, 0)
	}
};

#endif
