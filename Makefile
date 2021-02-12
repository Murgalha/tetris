all:
	@g++ -o tetris src/*.cpp -Iinclude -lSDL2 -lSDL2_ttf -O3

debug:
	@g++ -o tetris src/*.cpp -Iinclude -lSDL2 -lSDL2_ttf -O3 -g

run:
	@./tetris
