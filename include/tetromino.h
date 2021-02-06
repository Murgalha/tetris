#ifndef _TETROMINO_H_
#define _TETROMINO_H_

class Tetromino;

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
	Z,
	NSHAPES
} TetrominoShape;

class Tetromino {
public:
	Tetromino(TetrominoShape);
	Tetromino();
	~Tetromino();
	void render(SDL_Renderer *, Grid *);
	void check_and_move(Direction, Grid *);
	bool must_stop();
	std::vector<Block> blocks();
	Color color();
	static Color gen_color(TetrominoShape);
	static std::vector<Block> gen_blocks(TetrominoShape);
	static Tetromino *new_piece();
private:
	void _move(Direction);
	void _move_down();
	void _move_left();
	void _move_right();
	bool _can_move(Direction, Grid *);
	std::vector<Block> _blocks;
	int8_t _rightmost_position;
	int8_t _leftmost_position;
	int8_t _downmost_position;
	bool _must_stop;
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

const std::vector< std::vector< std::pair<int8_t, int8_t> > > POSITIONS {
	// I
	{
		std::make_pair(4, 0),
		std::make_pair(5, 0),
		std::make_pair(6, 0),
		std::make_pair(7, 0)
	},
	// J
	{
		std::make_pair(5, 0),
		std::make_pair(6, 0),
		std::make_pair(6, -1),
		std::make_pair(6, -2)
	},
	// L
	{
		std::make_pair(5, 0),
		std::make_pair(6, 0),
		std::make_pair(5, -1),
		std::make_pair(5, -2)
	},
	// O
	{
		std::make_pair(5, 0),
		std::make_pair(6, 0),
		std::make_pair(5, -1),
		std::make_pair(6, -1)
	},
	// S
	{
		std::make_pair(4, 0),
		std::make_pair(5, 0),
		std::make_pair(5, -1),
		std::make_pair(6, -1)
	},
	// T
	{
		std::make_pair(4, -1),
		std::make_pair(5, -1),
		std::make_pair(6, -1),
		std::make_pair(5, 0)
	},
	// Z
	{
		std::make_pair(4, -1),
		std::make_pair(5, -1),
		std::make_pair(5, 0),
		std::make_pair(6, 0)
	},
};

#endif
