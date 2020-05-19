#include "Game.h"
#include "TextureLoader.h"
#include "../ECS/ECS.h"
#include "../ECS/Components.h"
//Erormessages
using namespace DebugLog;
Scene scene;

SDL_Renderer* Game::renderer = nullptr; //This becaus SDL IS NOT INITIALIZED YET

auto& player(scene.AddEntity());

Game::Game(){}
Game::~Game(){}
void Game::Init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) //If 0 everything is OK!
	{
		//SuccessMSG("Subsystems Initialised!...");
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
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

	player.addComponent<PositionC>(0,0);
	player.addComponent<SpriteC>("img/Dirt.png");
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
	scene.Refresh();
	scene.Update();//This will update all entities and then components
	std::cout << player.getComponent<PositionC>().x() << " : " << player.getComponent<PositionC>().y() << "\n";
	if (player.getComponent<PositionC>().x() > 100)
	{
		player.getComponent<SpriteC>().SetTexture("img/Water.png");
	}
}
void Game::Render()
{
	SDL_RenderClear(renderer);
	scene.Draw();
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