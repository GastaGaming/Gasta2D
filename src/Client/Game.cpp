#include "Game.h"
#include "TextureLoader.h"
#include "../ECS/ECS.h"
#include "../ECS/Components.h"
#include "../Network.h"
#include <string> 
//Erormessages
using namespace DebugLog;
Scene scene;

SDL_Renderer* Game::renderer = nullptr; //This becaus SDL IS NOT INITIALIZED YET
auto& player(scene.AddEntity());
UDPConnection* udpConnection;
UDPpacket* packet;
#define DISPLAY_STRING_ROWS 20
char displayString[DISPLAY_STRING_ROWS][256];

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

	std::string IP = "192.168.1.44";
	int32_t remotePort = 1023;
	int32_t localPort = 1024;
	udpConnection = new UDPConnection();
	udpConnection->Init(IP, remotePort, localPort);
	for (int i = 0; i < DISPLAY_STRING_ROWS; i++) {
		for (int j = 0; j < 256; j++) {
			displayString[i][j] = 0;
		}
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
	scene.Refresh();
	scene.Update();//This will update all entities and then components
	std::cout << player.getComponent<PositionC>().x() << " : " << player.getComponent<PositionC>().y() << "\n";
	if (player.getComponent<PositionC>().x() > 100)
	{
		player.getComponent<SpriteC>().SetTexture("img/Water.png");
	}

	//Network
	packet = udpConnection->recievedData();
	#define PACKET_LEN packet->len
	#define PACKET_DATA packet->data
	static int currentRow = 0;
	if (packet != NULL) {
		for (int i = 0; i < PACKET_LEN; i++) {
			displayString[currentRow][i] = udpConnection->packet->data[i];
		}
		displayString[currentRow][PACKET_LEN] = 0;
		if (currentRow >= DISPLAY_STRING_ROWS) {
			currentRow = 0;
		}
		else {
			currentRow++;
		}
	}
	/*for (int i = 0; i < currentRow; i++) {
		if (displayString[i][0] != 0) {
			text(displayString[i], 20, 20, PACKET_LEN * 16, 16, 0, 0, 0);
		}
	}*/
	std::string send = std::to_string(player.getComponent<PositionC>().x()) + " : "  + std::to_string(player.getComponent<PositionC>().y());
	udpConnection->Send(send);
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