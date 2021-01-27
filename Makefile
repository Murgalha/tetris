all:
	@g++ -o tetris src/*.cpp -Iinclude -lSDL2 -O3

debug:
	@g++ -o tetris src/*.cpp -Iinclude -lSDL2 -O3 -g

run:
	@./tetris
