#ifndef _GRID_H_
#define _GRID_H_

class Grid;

#include <SDL2/SDL.h>
#include <cstdint>
#include <vector>
#include <utility>
#include "color.h"
#include "tetromino.h"
#include "utils.h"

class Grid {
public:
	Grid(uint8_t, uint8_t, uint8_t);
	~Grid();
	std::pair<int, int> to_pixels(int8_t, int8_t) const;
	void render(SDL_Renderer *);
	void fix_piece(Tetromino);
	bool can_move(Tetromino, Direction);
	uint32_t check_tetris();
	int to_pixels_x(int8_t) const;
	int to_pixels_y(int8_t) const;
	uint8_t width() const;
	uint8_t height() const;
	uint8_t border() const;
	std::vector< std::vector<Color> > mat();
private:
	uint8_t _width, _height, _border;
	void _draw_border(SDL_Renderer *);
	void _draw_mat(SDL_Renderer *);
	void _update_board_after_tetris(uint8_t);
	std::vector< std::vector<Color> > _mat;
};

#endif
