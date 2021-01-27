#include "game.h"
#include "tetris.h"

int main(int argc, char *argv[]) {
	Tetris *t = new Tetris();
	Game *g = new Game(t);

	g->run_loop();
	return 0;
}
