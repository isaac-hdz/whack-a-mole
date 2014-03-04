#include "cSDL_Setup.h"
#include "mole.h"

class cMain{
public:
	cMain();
	~cMain();
	void gameLoop();

private:
	// boolean to keep game loop running
	bool quit;
	// to keep track of the game's state (0: start, 1: game, 2: score)
	int gameState;
	// to get coordinates of mouse click and determine whether it is on a mole and which mole
	int locMole;

	// to keep track of hits and misses left (lives)
	int hits;
	int miss;

	// graphic info for start menu
	SDL_Texture * logo;
	SDL_Texture * start;
	SDL_Rect logoR;
	SDL_Rect startR;

	// graphic information for the HITS text
	SDL_Texture * hitTxtr;
	SDL_Rect hitRect;

	// graphic information for the MISSES text
	SDL_Texture * missTxtr;
	SDL_Rect missRect;

	// to store all of the numbers, and the places the numbers appear on the screen
	SDL_Texture * nums [10];
	SDL_Rect digits [5];

	// background graphic info
	SDL_Texture * grass;
	SDL_Rect grass_rect;

	// mole graphic info
	SDL_Texture * dug;
	SDL_Texture * out;
	SDL_Texture * hit;

	// to store the 9 moles' info
	mole * moles [9];

	// to start up SDL
	cSDL_Setup * sdl_setup;
};