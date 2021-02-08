#include "grid.h"
#include "utils.h"
#include "block.h"

// TODO: Use the color matrix for everything, including borders.
// Then, there would not be border checks, just color ones

Grid::Grid(uint8_t w, uint8_t h, uint8_t b) {
	this->_width = w;
	this->_height = h;
	this->_border = b;
	this->_mat = std::vector<std::vector<Color> >(h, std::vector<Color>(w));
}

Grid::~Grid() {

}

void Grid::render(SDL_Renderer *renderer) {
	this->_draw_border(renderer);
	this->_draw_mat(renderer);
}

std::pair<int, int> Grid::to_pixels(int8_t x, int8_t y) const {
	return std::make_pair(this->to_pixels_x(x), this->to_pixels_y(y));
}

int Grid::to_pixels_x(int8_t x) const {
	int w_step = WINDOW_WIDTH / (this->_width + 2*this->_border);
	return w_step * x;
}

int Grid::to_pixels_y(int8_t y) const {
	int h_step = WINDOW_HEIGHT / (this->_height + 2*this->_border);
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
			this->_mat[pos.second-1][pos.first-1] != BLACK)) {
			return false;
		}
	}
	return true;
}

// TODO: Use variables directly, not their getters
void Grid::_draw_border(SDL_Renderer *renderer) {
	Color c(100, 100, 100, 255);
	Block b(0, 0, c, 28);
	Block b2(0, this->height()+this->border(), c, 28);

	auto width = this->width() + 2*this->border();
	for(int i = 0; i < width; i++) {
		//b.render(renderer, this);
		//b.move_right();
		b2.render(renderer, this);
		b2.move_right();
	}

	b.new_position(0, 1);
	b2.new_position(this->width() + this->border(), 1);
	auto height = this->height() + 2*this->border();
	for(int i = 0; i < height - 1; i++) {
		b.render(renderer, this);
		b.move_down();
		b2.render(renderer, this);
		b2.move_down();
	}
}

void Grid::_draw_mat(SDL_Renderer *renderer) {
	for(int i = 0; i < this->_mat.size(); i++) {
		for(int j = 0; j < this->_mat[i].size(); j++) {
			auto color = this->_mat[i][j];
			Block b = Block(j+1, i+1, color, 28);
			b.render(renderer, this);
		}
	}
}

void Grid::fix_piece(Tetromino t) {
	auto color = t.color();
	for(auto block : t.blocks()) {
		auto pos = block.position();
		auto x = pos.first;
		auto y = pos.second;
		if(y-1 >= 0)
			this->_mat[y-1][x-1] = color;
	}
}

uint32_t Grid::check_tetris() {
	uint32_t points = 0;
	bool tetris;
	for(int i = this->_mat.size() - 1 ; i >= 0; i--) {
		tetris = true;
		for(auto color : this->_mat[i]) {
			if(color == BLACK) {
				tetris = false;
				break;
			}
		}
		if(tetris) {
			printf("We have a TETRIS!\n");
			// TODO: Use same ammount of points used in
			// original tetris
			points += 10;
			printf("Updating board...\n");
			this->_update_board_after_tetris(i);
			tetris = false;
		}
	}
	return points;
}

void Grid::_update_board_after_tetris(uint8_t row) {
	for(uint8_t i = row; i > 0; i--) {
		this->_mat[i] = this->_mat[i-1];
	}
	this->_mat[0] = std::vector<Color>(this->_width);
}
