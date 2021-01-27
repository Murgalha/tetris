#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <SDL2/SDL.h>

class GameState {
public:
	virtual void update() = 0;
	virtual void render(SDL_Renderer *) = 0;
	virtual bool has_ended() = 0;
};

#endif
