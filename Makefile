wam: wam.cpp
	g++ -o Whack-a-Mole wam.cpp main.cpp main.h cSDL_Setup.cpp cSDL_Setup.h mole.cpp mole.h -mwindows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

