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
	bool check_and_move(Direction, Grid *);
	bool can_move(Direction, Grid *);
	bool must_stop();
	void rotate(Grid *);
	std::vector<Block> &blocks();
	Color &color();
	static Color gen_color(TetrominoShape);
	static uint8_t gen_box_size(TetrominoShape);
	static std::pair<int8_t, int8_t> gen_pivot(TetrominoShape);
	static std::vector<Block> gen_blocks(TetrominoShape);
	static Tetromino *new_piece();
private:
	void _move(Direction);
	void _move_down();
	void _move_left();
	void _move_right();
	void _update_edges();
	std::vector<Block> _blocks;
	int8_t _rightmost_position;
	int8_t _leftmost_position;
	int8_t _downmost_position;
	std::pair<int8_t, int8_t> _pivot;
	bool _must_stop;
	Color _color;
	TetrominoShape _shape;
	uint8_t _box_size;
};

const std::vector< std::vector< std::pair<int8_t, int8_t> > > POSITIONS {
	// I
	{
		std::make_pair(5, 0),
		std::make_pair(5, -1),
		std::make_pair(5, -2),
		std::make_pair(5, -3)
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
