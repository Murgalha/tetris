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
	Tetromino();
	Tetromino(TetrominoShape);
	~Tetromino();
	void render(SDL_Renderer *, Grid *, bool outline = false);
	// mechanics functions
	bool maybe_move(Direction, Grid *);
	bool must_stop();
	void rotate(Grid *);
	void translate(int8_t, int8_t);
	// getters
	std::vector<Block> &blocks();
	Color &color();
	TetrominoShape shape() const;
private:
	void _set_piece(TetrominoShape);
	void _move(Direction);
	std::vector<Block> _blocks;
	std::pair<int8_t, int8_t> _pivot;
	bool _must_stop;
	Color _color;
	TetrominoShape _shape;
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
