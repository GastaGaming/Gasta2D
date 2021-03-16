//Using SDL and standard IO
//#include <SDL.h>
#include <SDL.h>
#undef main
#include "Game.h"
Game* game = nullptr;
using namespace DebugLog;
int main(int argc, const char* argv[])
{
	const int FPS = 60;
	const int FRAMEDELAY = 1000 / FPS;
	Uint32 frameStar;
	float_t frameTime;
	game = new Game();
	game->Init("Gasta2D", 1280, 720, false);
	while (game->running())
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