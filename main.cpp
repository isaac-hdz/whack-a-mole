#include "main.h"
#include <iostream>
#include <sstream>

// function to create SDL_Rect's faster
SDL_Rect setRectangle(int x, int y, int w, int h){
	SDL_Rect r;
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	return r;
}

// helper function to determine which mole was clicked
int locateMoleHelper(int base, int x){
	if(x>0 && x<64){
		return base;
	}
	if(x>63 && x<128){
		return base+3;
	}
	if(x>127 && x<192){
		return base+6;

	}
}

// function to determine which mole was clicked
int locateMole (int x, int y){
	if(y>63 && y<128){
		return locateMoleHelper(0,x);
	}
	if(y>127 && y<192){
		return locateMoleHelper(1,x);

	}
	if(y>191 && y<256){
		return locateMoleHelper(2,x);
	}
}

cMain::cMain(){
	// initialize everything!
	quit = false;	
	sdl_setup = new cSDL_Setup(&quit);

	hits = 0;
	miss = 9;

	hitTxtr = nullptr;
	hitTxtr = IMG_LoadTexture(sdl_setup->getRend(),"hit_text.bmp");
	if(grass == nullptr){
		std::cout << "ERROR: Couldn't load text 1.\n";
		quit = true;
	}
	hitRect = setRectangle(34,10,28,10);

	missTxtr = nullptr;
	missTxtr = IMG_LoadTexture(sdl_setup->getRend(),"miss_text.bmp");
	if(grass == nullptr){
		std::cout << "ERROR: Couldn't load text 2.\n";
		quit = true;
	}
	missRect = setRectangle(123,10,41,10);

	for(int i=0; i<10; i++){
		nums[i] = nullptr;
	}
	nums[0] = IMG_LoadTexture(sdl_setup->getRend(),"0.bmp");
	nums[1] = IMG_LoadTexture(sdl_setup->getRend(),"1.bmp");
	nums[2] = IMG_LoadTexture(sdl_setup->getRend(),"2.bmp");
	nums[3] = IMG_LoadTexture(sdl_setup->getRend(),"3.bmp");
	nums[4] = IMG_LoadTexture(sdl_setup->getRend(),"4.bmp");
	nums[5] = IMG_LoadTexture(sdl_setup->getRend(),"5.bmp");
	nums[6] = IMG_LoadTexture(sdl_setup->getRend(),"6.bmp");
	nums[7] = IMG_LoadTexture(sdl_setup->getRend(),"7.bmp");
	nums[8] = IMG_LoadTexture(sdl_setup->getRend(),"8.bmp");
	nums[9] = IMG_LoadTexture(sdl_setup->getRend(),"9.bmp");
	for(int i=0; i<10; i++){
		if(nums[0] == nullptr){
			std::cout << "ERROR: Couldn't load " << i << " image.\n";
			quit = true;
		}
	}

	digits[0] = setRectangle(34,20,10,10);
	digits[1] = setRectangle(44,20,10,10);	
	digits[2] = setRectangle(54,20,10,10);	
	digits[3] = setRectangle(64,20,10,10);	
	digits[4] = setRectangle(123,20,10,10);

	grass = nullptr;
	grass = IMG_LoadTexture(sdl_setup->getRend(),"bg_0.bmp");
	if(grass == nullptr){
		std::cout << "ERROR: Couldn't load background.\n";
		quit = true;
	}
	grass_rect = setRectangle(0,0,196,262);

	dug = nullptr;
	dug = IMG_LoadTexture(sdl_setup->getRend(),"dugout_1.bmp");
	if(dug == nullptr){
		std::cout << "ERROR: Couldn't load dug.\n";
		quit = true;
	}

	out = nullptr;
	out = IMG_LoadTexture(sdl_setup->getRend(),"out_1.bmp");
	if(out == nullptr){
		std::cout << "ERROR: Couldn't load out.\n";
		quit = true;
	}

	hit = nullptr;
	hit = IMG_LoadTexture(sdl_setup->getRend(),"hit_1.bmp");
	if(hit == nullptr){
		std::cout << "ERROR: Couldn't load hit.\n";
		quit = true;
	}

	moles[0] = new mole(dug, setRectangle(0,64,64,64));
	moles[1] = new mole(dug, setRectangle(0,128,64,64));
	moles[2] = new mole(dug, setRectangle(0,192,64,64));
	moles[3] = new mole(dug, setRectangle(64,64,64,64));
	moles[4] = new mole(dug, setRectangle(64,128,64,64));
	moles[5] = new mole(dug, setRectangle(64,192,64,64));
	moles[6] = new mole(dug, setRectangle(128,64,64,64));
	moles[7] = new mole(dug, setRectangle(128,128,64,64));
	moles[8] = new mole(dug, setRectangle(128,192,64,64));
}

cMain::~cMain(){
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(dug);
	SDL_DestroyTexture(out);
	SDL_DestroyTexture(hit);
}

void cMain::gameLoop(){
	while (!quit && sdl_setup->getEvent()->type != SDL_QUIT){
		SDL_PollEvent(sdl_setup->getEvent());
		SDL_RenderClear(sdl_setup->getRend());

		// background and text
		SDL_RenderCopy(sdl_setup->getRend(), grass, nullptr, &grass_rect);
		SDL_RenderCopy(sdl_setup->getRend(), hitTxtr, nullptr, &hitRect);
		SDL_RenderCopy(sdl_setup->getRend(), missTxtr, nullptr, &missRect);

		// output the score
		if(hits < 10){
			SDL_RenderCopy(sdl_setup->getRend(),nums[hits],nullptr,&digits[0]);
		}
		else if(hits < 100){
			SDL_RenderCopy(sdl_setup->getRend(),nums[(hits-hits%10)/10],nullptr,&digits[0]);
			SDL_RenderCopy(sdl_setup->getRend(),nums[hits%10],nullptr,&digits[1]);
		}
		else if(hits < 1000){
			SDL_RenderCopy(sdl_setup->getRend(),nums[(hits-hits%100)/100],nullptr,&digits[0]);
			SDL_RenderCopy(sdl_setup->getRend(),nums[((hits-hits%10)/10)%10],nullptr,&digits[1]);
			SDL_RenderCopy(sdl_setup->getRend(),nums[(hits%10)%10],nullptr,&digits[2]);
		}
		else if(hits < 9999){
			SDL_RenderCopy(sdl_setup->getRend(),nums[(hits-hits%1000)/1000],nullptr,&digits[0]);
			SDL_RenderCopy(sdl_setup->getRend(),nums[((hits-hits%100)/100)%10],nullptr,&digits[1]);
			SDL_RenderCopy(sdl_setup->getRend(),nums[((hits-hits%10)/10)%10],nullptr,&digits[2]);
			SDL_RenderCopy(sdl_setup->getRend(),nums[hits%10],nullptr,&digits[3]);
		}
		else{
			SDL_RenderCopy(sdl_setup->getRend(),nums[9],nullptr,&digits[0]);
			SDL_RenderCopy(sdl_setup->getRend(),nums[9],nullptr,&digits[1]);
			SDL_RenderCopy(sdl_setup->getRend(),nums[9],nullptr,&digits[2]);
			SDL_RenderCopy(sdl_setup->getRend(),nums[9],nullptr,&digits[3]);
		}

		// output misses left (lives)
		SDL_RenderCopy(sdl_setup->getRend(),nums[miss],nullptr,&digits[4]);

		// handle the moles
		for(int i=0; i<9; i++){
			// if mole is inside, randomly decide if it should come out
			if(moles[i]->currImg == dug){
				if(rand()%2000+1 == 1){
					moles[i]->currImg = out;
					moles[i]->waitTime = 3000;
				}
			}
			else{
				// if wait time is over
 				if(moles[i]->waitTime == 0){
 					// and mole has not been hit, take away a life
 					if(moles[i]->currImg == out){
 						miss--;
						if(miss == 0)
							quit = true; 						
 					}
 					// return underground
					moles[i]->currImg = dug;
				}
				else
					moles[i]->waitTime--;
			}

			SDL_RenderCopy(sdl_setup->getRend(), moles[i]->currImg, nullptr, &(moles[i]->rect));
		}

		// detect mouse click and verify if a mole was clicked
		if(sdl_setup->getEvent()->type == SDL_MOUSEBUTTONDOWN){
			if(sdl_setup->getEvent()->motion.y > 63){
				locMole = locateMole(sdl_setup->getEvent()->motion.x, sdl_setup->getEvent()->motion.y);
				if(moles[locMole]->currImg == out){
					hits++;
					moles[locMole]->currImg = hit;
					moles[locMole]->waitTime = 500;
				}
			}
		}

		SDL_RenderPresent(sdl_setup->getRend());
	}
}