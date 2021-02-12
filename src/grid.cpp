#include "grid.h"
#include "utils.h"
#include "block.h"

Grid::Grid(uint8_t w, uint8_t h, uint8_t b) {
	this->_width = w;
	this->_height = h;
	this->_border = b;
	this->_mat = std::vector< std::vector<Color> >
		(h + this->_border,
		 std::vector<Color>(w + 2*this->_border));
	this->_set_mat();
}

Grid::~Grid() {

}

void Grid::render(SDL_Renderer *renderer) {
	Block b(28);
	for(int y = 0; y < this->_mat.size(); y++) {
		for(int x = 0; x < this->_mat[y].size(); x++) {
			b.new_position(x, y);
			b.new_color(this->_mat[y][x]);
			b.render(renderer, this);
		}
	}
}

void Grid::_set_mat() {
	for(int y = 0; y < this->_mat.size(); y++) {
		for(int x = 0; x < this->_mat[y].size(); x++) {
			if(x == 0 ||
			   x == this->_mat[y].size() - 1 ||
			   y == this->_mat.size() - 1)
				this->_mat[y][x] = GREY;
			else
				this->_mat[y][x] = BLACK;
		}
	}
}

std::pair<int, int> Grid::to_pixels(int8_t x, int8_t y) const {
	return std::make_pair(this->to_pixels_x(x) + 1, this->to_pixels_y(y) + 1);
}

int Grid::to_pixels_x(int8_t x) const {
	int w_step = GRID_WIDTH / this->_mat[0].size();
	return w_step * x;
}

int Grid::to_pixels_y(int8_t y) const {
	int h_step = GRID_HEIGHT / this->_mat.size();
	return h_step * y;
}

uint8_t Grid::width() const {
	return this->_width;
}

uint8_t Grid::height() const {
	return this->_height;
}

uint8_t Grid::border() const {
	return this->_border;
}

bool Grid::can_move(Tetromino t, Direction d) {
	for(auto block : t.blocks()) {
		std::pair<uint8_t, uint8_t> offset = std::make_pair(0, 0);
		auto pos = block.position();
		switch(d) {
		case Right:
			offset.first = 1;
			break;
		case Left:
			offset.first = -1;
			break;
		case Down:
			offset.second = 1;
			break;
		default:
			break;
		}
		pos.first += offset.first;
		pos.second += offset.second;

		if(pos.second > this->_height ||
		   pos.first > this->_width ||
		   (pos.second > 0 &&
			this->_mat[pos.second][pos.first] != BLACK)) {
			return false;
		}
	}
	return true;
}

void Grid::fix_piece(Tetromino t) {
	auto color = t.color();
	for(auto block : t.blocks()) {
		auto pos = block.position();
		auto x = pos.first;
		auto y = pos.second;
		if(y >= 0)
			this->_mat[y][x] = color;
	}
}

uint32_t Grid::check_tetris() {
	uint32_t points = 0;
	bool tetris;
	// _mat.size() - 2 to exclude bottom border row
	for(int i = this->_mat.size() - 2 ; i >= 0; i--) {
		tetris = true;
		for(auto color : this->_mat[i]) {
			if(color == BLACK) {
				tetris = false;
				break;
			}
		}
		if(tetris) {
			printf("We have a TETRIS! on row %d\n", i);
			// TODO: Use same ammount of points used in
			// original tetris
			points += 10;
			printf("Updating board...\n");
			this->_update_board_after_tetris(i);
			i++;
		}
	}
	return points;
}

void Grid::_update_board_after_tetris(uint8_t row) {
	for(uint8_t i = row; i > 0; i--) {
		this->_mat[i] = this->_mat[i-1];
	}
	// Create new row and put grey border on the edges
	this->_mat[0] = std::vector<Color>(this->_width + 2*this->_border);
	this->_mat[0][0] = GREY;
	this->_mat[0][this->_mat[0].size()-1] = GREY;
}
