#include "Game.h"
#include "TextureLoader.h"
#include "Map.h"
#include "OrbSpawnerC.h"
//#include "../Network.h"
#include <string> 
//Erormessages
using namespace DebugLog;
Map* map;
SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr; //This becaus SDL IS NOT INITIALIZED YET
std::vector<ColliderC*> Game::colliders;
CameraC* Game::camera;
Scene scene;
auto& camerar(scene.AddEntity());
auto& player(scene.AddEntity());
auto& wall(scene.AddEntity());
auto& orbSpawner(scene.AddEntity());

auto& tiles(scene.getGroup(Game::groupMap));
auto& players(scene.getGroup(Game::groupPlayers));
auto& enemies(scene.getGroup(Game::groupEnemies));
auto& orbs(scene.getGroup(Game::groupOrbs));
//UDPConnection* udpConnection;
//UDPpacket* packet;
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
	map = new Map("img/map.tga", 4, 32, scene);
	map->LoadMap();
	//Map::LoadMap("img/map.tga");

	camerar.addComponent<CameraC>();

	player.addComponent<TransformC>(500,1000,2);
	int numOfAnimation = 4;
	std::vector<int> framesInAnimation = { 4,4,4,4 };
	std::vector<int> delayPerAnimation = { 50,50,50,50};

	player.addComponent<SpriteC>("img/SpaceShip.png", true, numOfAnimation, framesInAnimation, delayPerAnimation);
	//player.addComponent<SpriteC>("img/DirtA.png", true);
	camerar.getComponent<CameraC>().AddTarget(&player);
	camera = &camerar.getComponent<CameraC>();
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderC>("player");
	player.AddGroup(groupMap);

	wall.addComponent<TransformC>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteC>("img/Dirt.png");
	wall.addComponent<ColliderC>("wall");
	wall.AddGroup(groupMap);

	orbSpawner.addComponent<OrbSpawner>(10, scene);

	/*std::string IP = "192.168.1.44";
	int32_t remotePort = 1023;
	int32_t localPort = 1024;
	udpConnection = new UDPConnection();
	udpConnection->Init(IP, remotePort, localPort);
	for (int i = 0; i < DISPLAY_STRING_ROWS; i++) {
		for (int j = 0; j < 256; j++) {
			displayString[i][j] = 0;
		}
	}*/
	//std::string input = "logIn";
	//std::string outPut;
	//bool inputOk = false;
	//std::cout << "Input your user Name\n" << std::endl;
	//std::cin >> input;
	//int dap = 0;
	//udpConnection->Send(input);
	//while (!udpConnection->recievedData())
	//{
	//	dap++;
	//	if (dap < 100)
	//	{
	//		udpConnection->Send(input);
	//		dap = 0;
	//	}
	//	packet = udpConnection->recievedData();
	//}
	//for (int i = 0; i < packet->len; i++)//Collect the data
	//{
	//	//std::cout << (char)packet->data[i];
	//	outPut += (char)packet->data[i];
	//	//cout << sData << endl;
	//}
	//std::cout << "JEEEEE" << std::endl;
}
void Game::HandleEvents()
{
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
	//cam->Update();
	//player.getComponent<TransformC>().position.Add(Vector2D(5, 0));

	//std::cout << player.getComponent<TransformC>().position << "\n"; !!!!!!!!!!!!!!!!!!!!!!
	
	/*if (player.getComponent<TransformC>().position.x > 100)
	{
		player.getComponent<SpriteC>().SetTexture("img/Water.png");
	}*/

	//For the collision check record position before update
	ColliderC playerCol = player.getComponent<ColliderC>();
	Vector2D playerPos = player.getComponent<TransformC>().position;
	std::vector<Vector2D> orbPos;
	for each (Entity * or in orbSpawner.getComponent<OrbSpawner>().orbs)
	{
		orbPos.push_back(or->getComponent<TransformC>().position);
	}
	//Update objects these must hapen before update
	scene.Refresh();
	scene.Update();//This will update all entities and then components

	if (Collision::AABB(player.getComponent<ColliderC>().collider, wall.getComponent<ColliderC>().collider))
	{
		//player.getComponent<TransformC>().scale = 1;
		//player.getComponent<TransformC>().velocity * -1;
		player.getComponent<TransformC>().position = playerPos;
		std::cout << "WALL HIT! : AU YOU HURTING ME" << "\n";
	}
	for (auto cc : colliders)
	{
		int oCount = 0;
		if (Collision::AABB(playerCol, *cc))
		{
			//player.getComponent<TransformC>().scale = 4;
			//player.getComponent<TransformC>().velocity * 0;
			player.getComponent<TransformC>().position = playerPos;
			std::cout << "WALL HIT! : AU YOU HURTING ME" << "\n";
		}
		for each (Entity* or in orbSpawner.getComponent<OrbSpawner>().orbs)
		{
			if (Collision::AABB(or->getComponent<ColliderC>(), *cc))
			{
				or ->getComponent<TransformC>().position = orbPos[oCount];
				or->getComponent<TransformC>().velocity * -1;
				//or->getComponent<TransformC>().position.x = or ->getComponent<TransformC>().position.x + or->getComponent<TransformC>().velocity.x * 5;
				//or->getComponent<TransformC>().position.y = or ->getComponent<TransformC>().position.y + or->getComponent<TransformC>().velocity.y * 5;


			}
			oCount++;
		}
	}

	//Network
	/*packet = udpConnection->recievedData();
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
	}*/
	/*for (int i = 0; i < currentRow; i++) {
		if (displayString[i][0] != 0) {
			text(displayString[i], 20, 20, PACKET_LEN * 16, 16, 0, 0, 0);
		}
	}*/
	//std::string send = std::to_string(player.getComponent<PositionC>().x()) + " : " + std::to_string(player.getComponent<PositionC>().y());
	//udpConnection->Send(send);
}

void Game::Render()
{
	SDL_RenderClear(renderer);
	for (auto& t : tiles)
	{
		t->Draw();
	}
	for (auto& p : players)
	{
		p->Draw();
	}
	for (auto& e : enemies)
	{
		e->Draw();
	}
	for (auto& o : orbs)
	{
		o->Draw();
	}
	//scene.Draw();
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