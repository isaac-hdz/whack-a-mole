/* 
Project Title: 			Whack-A-Mole (wam) v1.0
Project Developer: 		Isaac Hernandez
Project Date:			February 2014
Project Description:	Whack-A-Mole is my first attempt at using C++, SDL2, and SDL_image to create a game. 
						My previous games were all created using GameMaker but I never felt like I had enough
						control over the functionality, sometimes I even felt like using GameMaker was
						cheating. So I decided to go ahead and use C++ and some of its libraries to make
						this, my first "real" prototype.
Project Gameplay:		Whack-A-Mole is a game in which the user must try to "whack", or click, as many moles
						as possible before 9 of them manage to escape. As it is a prototype, there is not much
						user interface and the game exits after the 9th mole escapes.
Project Future:			Maybe someday I will add a user interface

The files included are:

	wam.cpp:
		This is the main file which calls everything else.
	cSDL_Setup.cpp & cSDL_Setup.h:
		This files are for setting up SDL2. Aside from the specific window information in cSDL_Setup.cpp,
		these files can be re-used to set up SDL for another project.
	main.cpp & main.h:
		main.h sets up all the variables and main.cpp defines all of the game's functionality. cMain(), the 
		constructor loads up all of the information and gameLoop() process clicks and time to manipulate the
		scoreboard and the moles.
	tons of bmp files:
		Unfortunately, I had trouble loading png files, so I had to load only bmp files. If I can ever get png
		files to load, I might revisit this project so as to reduce the size.

*/

#include "main.h"
#include <iostream>

int main( int argc, char* args[] ) { 
	// set up
	cMain cm;
	// play
	cm.gameLoop();

	return 0;
} 