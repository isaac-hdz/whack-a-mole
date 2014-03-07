#include <iostream>
#include <string>
#include "main.h"


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

void outputScore(cSDL_Setup* csdl, SDL_Texture* numsTxts[], SDL_Rect digitSpots[], int hitsCurr){
	if(hitsCurr < 10){
		SDL_RenderCopy(csdl->getRend(),numsTxts[hitsCurr],nullptr,&digitSpots[0]);
	}
	else if(hitsCurr < 100){
		SDL_RenderCopy(csdl->getRend(),numsTxts[(hitsCurr-hitsCurr%10)/10],nullptr,&digitSpots[0]);
		SDL_RenderCopy(csdl->getRend(),numsTxts[hitsCurr%10],nullptr,&digitSpots[1]);
	}
	else if(hitsCurr < 1000){
		SDL_RenderCopy(csdl->getRend(),numsTxts[(hitsCurr-hitsCurr%100)/100],nullptr,&digitSpots[0]);
		SDL_RenderCopy(csdl->getRend(),numsTxts[((hitsCurr-hitsCurr%10)/10)%10],nullptr,&digitSpots[1]);
		SDL_RenderCopy(csdl->getRend(),numsTxts[(hitsCurr%10)%10],nullptr,&digitSpots[2]);
	}
	else if(hitsCurr < 9999){
		SDL_RenderCopy(csdl->getRend(),numsTxts[(hitsCurr-hitsCurr%1000)/1000],nullptr,&digitSpots[0]);
		SDL_RenderCopy(csdl->getRend(),numsTxts[((hitsCurr-hitsCurr%100)/100)%10],nullptr,&digitSpots[1]);
		SDL_RenderCopy(csdl->getRend(),numsTxts[((hitsCurr-hitsCurr%10)/10)%10],nullptr,&digitSpots[2]);
		SDL_RenderCopy(csdl->getRend(),numsTxts[hitsCurr%10],nullptr,&digitSpots[3]);
	}
	else{
		SDL_RenderCopy(csdl->getRend(),numsTxts[9],nullptr,&digitSpots[0]);
		SDL_RenderCopy(csdl->getRend(),numsTxts[9],nullptr,&digitSpots[1]);
		SDL_RenderCopy(csdl->getRend(),numsTxts[9],nullptr,&digitSpots[2]);
		SDL_RenderCopy(csdl->getRend(),numsTxts[9],nullptr,&digitSpots[3]);
	}
}

cMain::cMain(){
	// initialize everything!
	quit = false;
	gameState = 0;
	sdl_setup = new cSDL_Setup(&quit);

	logo = nullptr;
	logo = IMG_LoadTexture(sdl_setup->getRend(),"logo.png");
	if(logo == nullptr){
		std::cout << "ERROR: Couldn't load logo 1.\n";
		quit = true;
	}
	logoR = setRectangle(36,32,140,64);

	start = nullptr;
	start = IMG_LoadTexture(sdl_setup->getRend(),"start.png");
	if(start == nullptr){
		std::cout << "ERROR: Couldn't load start 1.\n";
		quit = true;
	}
	startR = setRectangle(48,128,100,32);

	highScore = nullptr;
	highScore = IMG_LoadTexture(sdl_setup->getRend(),"highScore.png");
	if(hsBox == nullptr){
		std::cout << "ERROR: Couldn't load highScore.\n";
		quit = true;
	}

	hsBox = nullptr;
	hsBox = IMG_LoadTexture(sdl_setup->getRend(),"hsBox.png");
	if(hsBox == nullptr){
		std::cout << "ERROR: Couldn't load hsBox 1.\n";
		quit = true;
	}
	hsBoxR = setRectangle(48,196,100,32);
	highScoreR = setRectangle(48,191,100,32);

	digitsHiS[0] = setRectangle(68,213,10,10);
	digitsHiS[1] = setRectangle(78,213,10,10);	
	digitsHiS[2] = setRectangle(88,213,10,10);	
	digitsHiS[3] = setRectangle(98,213,10,10);

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
	nums[0] = IMG_LoadTexture(sdl_setup->getRend(),"0.png");
	nums[1] = IMG_LoadTexture(sdl_setup->getRend(),"1.png");
	nums[2] = IMG_LoadTexture(sdl_setup->getRend(),"2.png");
	nums[3] = IMG_LoadTexture(sdl_setup->getRend(),"3.png");
	nums[4] = IMG_LoadTexture(sdl_setup->getRend(),"4.png");
	nums[5] = IMG_LoadTexture(sdl_setup->getRend(),"5.png");
	nums[6] = IMG_LoadTexture(sdl_setup->getRend(),"6.png");
	nums[7] = IMG_LoadTexture(sdl_setup->getRend(),"7.png");
	nums[8] = IMG_LoadTexture(sdl_setup->getRend(),"8.png");
	nums[9] = IMG_LoadTexture(sdl_setup->getRend(),"9.png");
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
	dug = IMG_LoadTexture(sdl_setup->getRend(),"dugout_0.png");
	if(dug == nullptr){
		std::cout << "ERROR: Couldn't load dug.\n";
		quit = true;
	}

	out = nullptr;
	out = IMG_LoadTexture(sdl_setup->getRend(),"out_0.png");
	if(out == nullptr){
		std::cout << "ERROR: Couldn't load out.\n";
		quit = true;
	}

	hit = nullptr;
	hit = IMG_LoadTexture(sdl_setup->getRend(),"hit_0.png");
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

	scoreBox = nullptr;
	scoreBox = IMG_LoadTexture(sdl_setup->getRend(),"scoreBox.png");
	if(scoreBox == nullptr){
		std::cout << "ERROR: Couldn't load scoreBox.\n";
		quit = true;
	}
	scoreBoxR = setRectangle(28,32,140,96);

	tryAgain = nullptr;
	tryAgain = IMG_LoadTexture(sdl_setup->getRend(),"tryagain.png");
	if(tryAgain == nullptr){
		std::cout << "ERROR: Couldn't load try again.\n";
		quit = true;
	}

	yourScore = nullptr;
	yourScore = IMG_LoadTexture(sdl_setup->getRend(),"yourScore.png");
	if(yourScore == nullptr){
		std::cout << "ERROR: Couldn't load yourScore.\n";
		quit = true;
	}
	yourScoreR = setRectangle(48,32,100,32);

	newHigh = nullptr;
	newHigh = IMG_LoadTexture(sdl_setup->getRend(),"new.png");
	if(yourScore == nullptr){
		std::cout << "ERROR: Couldn't load new.\n";
		quit = true;
	}
	newHighR = setRectangle(0,72,100,32);

	digitsYS[0] = setRectangle(68,54,10,10);
	digitsYS[1] = setRectangle(78,54,10,10);	
	digitsYS[2] = setRectangle(88,54,10,10);	
	digitsYS[3] = setRectangle(98,54,10,10);

	if(std::ifstream("hs.txt")){
		std::string line;
		std::ifstream hsf("hs.txt");
		hsf >> theHS;
		hsf.close();
	}
	else
		theHS = 0;
}

cMain::~cMain(){
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(dug);
	SDL_DestroyTexture(out);
	SDL_DestroyTexture(hit);
	
	// record the high score
	if(std::ifstream("hs.txt"))
		remove("hs.txt");		
	std::ofstream hsFile("hs.txt");
	hsFile << theHS;
}

void cMain::gameLoop(){
	while (!quit && sdl_setup->getEvent()->type != SDL_QUIT){
		SDL_PollEvent(sdl_setup->getEvent());
		SDL_RenderClear(sdl_setup->getRend());

		// background and text
		SDL_RenderCopy(sdl_setup->getRend(), grass, nullptr, &grass_rect);

		// if game is on start menu
		if(gameState==0){
			// display start menu graphics
			SDL_RenderCopy(sdl_setup->getRend(), logo, nullptr, &logoR);
			SDL_RenderCopy(sdl_setup->getRend(), start, nullptr, &startR);
			SDL_RenderCopy(sdl_setup->getRend(), hsBox, nullptr, &hsBoxR);
			SDL_RenderCopy(sdl_setup->getRend(), highScore, nullptr, &highScoreR);
			outputScore(sdl_setup, nums, digitsHiS, theHS);

			// detect mouse click and verify if start was clicked
			if(sdl_setup->getEvent()->type == SDL_MOUSEBUTTONDOWN){
				if(sdl_setup->getEvent()->motion.y > 127 && sdl_setup->getEvent()->motion.y < 161 &&
				   sdl_setup->getEvent()->motion.x > 48 && sdl_setup->getEvent()->motion.x < 149){
					highScoreR = setRectangle(48,72,100,32);
					digitsHiS[0] = setRectangle(68,94,10,10);
					digitsHiS[1] = setRectangle(78,94,10,10);	
					digitsHiS[2] = setRectangle(88,94,10,10);	
					digitsHiS[3] = setRectangle(98,94,10,10);
					hits = 0;
					miss = 9;
					newHS = false;
					gameState = 1;
				}
			}
		}

		// if game has begun
		else if(gameState==1){
			SDL_RenderCopy(sdl_setup->getRend(), hitTxtr, nullptr, &hitRect);
			SDL_RenderCopy(sdl_setup->getRend(), missTxtr, nullptr, &missRect);

			// output the score 
			outputScore(sdl_setup, nums, digits, hits);

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
							if(miss == 0){
								gameState = 2; 														
							}
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
		}

		// else game is on after-loss score state
		else{
			// graphics for large white box
			SDL_RenderCopy(sdl_setup->getRend(), scoreBox, nullptr, &scoreBoxR);

			// graphics for the score the player just got
			SDL_RenderCopy(sdl_setup->getRend(), yourScore, nullptr, &yourScoreR);
			outputScore(sdl_setup, nums, digitsYS, hits);

			// graphics for the user's all-time high score
			if(hits > theHS){
				theHS = hits;
				newHS = true;
			}
			if(newHS)
				SDL_RenderCopy(sdl_setup->getRend(), newHigh, nullptr, &newHighR);


			SDL_RenderCopy(sdl_setup->getRend(), highScore, nullptr, &highScoreR);
			outputScore(sdl_setup, nums, digitsHiS, theHS);

			// graphics for try again box
			SDL_RenderCopy(sdl_setup->getRend(), hsBox, nullptr, &hsBoxR);
			SDL_RenderCopy(sdl_setup->getRend(), tryAgain, nullptr, &hsBoxR);


			// detect mouse click and verify if try again was clicked
			if(sdl_setup->getEvent()->type == SDL_MOUSEBUTTONDOWN){
				if(sdl_setup->getEvent()->motion.y > 191 && sdl_setup->getEvent()->motion.y < 227 &&
				   sdl_setup->getEvent()->motion.x > 48 && sdl_setup->getEvent()->motion.x < 149){
					highScoreR = setRectangle(48,191,100,32);
					digitsHiS[0] = setRectangle(68,213,10,10);
					digitsHiS[1] = setRectangle(78,213,10,10);	
					digitsHiS[2] = setRectangle(88,213,10,10);	
					digitsHiS[3] = setRectangle(98,213,10,10);
					gameState = 0;
				}
			}
		}
		SDL_RenderPresent(sdl_setup->getRend());
	}
}