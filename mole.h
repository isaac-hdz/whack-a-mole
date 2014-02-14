#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class mole{
public:
	mole(SDL_Texture * t, SDL_Rect r);
	~mole();

	SDL_Texture * currImg;
	SDL_Rect rect;
	int waitTime;
};