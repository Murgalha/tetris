#ifndef _SDLDESTROYER_H_
#define _SDLDESTROYER_H_

struct SDL_Deleter {
	void operator()(SDL_Window *w) const {
		SDL_DestroyWindow(w);
	}
	void operator()(SDL_Renderer *r) const {
		SDL_DestroyRenderer(r);
	}
};

#endif
