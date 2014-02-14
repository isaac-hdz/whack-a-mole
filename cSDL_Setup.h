#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// class to set up SDL: window, renderer, and event handler
class cSDL_Setup{
public:
	cSDL_Setup(bool * quit);
	~cSDL_Setup();

	SDL_Renderer * getRend();
	SDL_Event * getEvent();

private:
	SDL_Window* win;
	SDL_Renderer* ren;
	SDL_Event* ev;
};