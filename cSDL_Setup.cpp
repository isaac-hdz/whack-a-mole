#include "cSDL_Setup.h"
#include <iostream>

cSDL_Setup::cSDL_Setup(bool * quit){
	SDL_Init(SDL_INIT_VIDEO);
	
	win = nullptr;
	win = SDL_CreateWindow("Whack-a-Mole!",100,100,192,256,SDL_WINDOW_SHOWN);
	if(win == nullptr){
		std::cout << "ERROR: Window was not created.\n";
		*quit = true;
	}

	ren = nullptr;
	ren = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);

	ev = new SDL_Event();
}

cSDL_Setup::~cSDL_Setup(){
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
	delete ev;
	SDL_Quit();
}

SDL_Renderer * cSDL_Setup::getRend(){
	return ren;
}

SDL_Event * cSDL_Setup::getEvent(){
	return ev;
}