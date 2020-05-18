/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
//#include <SDL.h>
#include "Game.h"
Game* game = nullptr;
int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int FRAMEDELAY = 1000 / FPS;
	Uint32 frameStar;
	int frameTime;
	game = new Game();
	game->Init("Gasta2D", 800, 640, false);
	while (game->Running())
	{
		frameStar = SDL_GetTicks();
		game->HandleEvents();
		game->Update();
		game->Render();
		frameTime = SDL_GetTicks() - frameStar;
		if (FRAMEDELAY > frameTime)
		{
			SDL_Delay(FRAMEDELAY - frameTime);
		}
	}
	game->Clean();
	return 0;
}