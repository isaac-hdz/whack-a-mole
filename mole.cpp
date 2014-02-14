#include "mole.h"

mole::mole(SDL_Texture * t, SDL_Rect r){
	currImg = t;
	rect = r;
	waitTime = 0;
}

mole::~mole(){
	SDL_DestroyTexture(currImg);
}