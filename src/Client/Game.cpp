#include "Game.h"
//Erormessages
using namespace DebugLog;
Game::Game()
{
}

Game::~Game()
{
}
void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) //If 0 everything is OK!
	{
		//SuccessMSG("Subsystems Initialised!...");
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			SuccessMSG("Window created");
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SuccessMSG("Renderer created!");
		}
		isRunning = true;
	}
	else
	{
		ErrorMSG("Game Init() failed!");
		isRunning = false;
	}
}
void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;
	default:
		break;
	}
}
void Game::Update()
{
	//Update objects
}
void Game::Render()
{
	SDL_RenderClear(renderer);
	//Render objects
	SDL_RenderPresent(renderer);
}
void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	SuccessMSG("Game cleaned");
}