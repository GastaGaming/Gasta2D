#include "SDL_image.h"
#include <iostream>

class Game
{
public:
	Game();
	~Game();

	void Init(const char* title, int width, int height, bool fullscreen);
	void HandleEvents();
	void Update();
	void Render();
	void Clean();

	bool running() { return isRunning; };
	static SDL_Renderer *renderer;
	static SDL_Event event;
private:
	bool isRunning;
	SDL_Window* window;
};

namespace DebugLog
{
	static void Warning(const char* message)
	{
		printf("%c[%dm", 0x1B, 33);//Yellow
		std::cout << message << std::endl;
	}
	static void ErrorMSG(const char* message)
	{
		printf("%c[%dm", 0x1B, 31);//Red
		std::cout << message << std::endl;
	}
	static void LogMSG(const char* message)
	{
		printf("%c[%dm", 0x1B, 39);//White
		std::cout << message << std::endl;
	}
	static void SuccessMSG(const char* message)
	{
		printf("%c[%dm", 0x1B, 32);//Green
		std::cout << message << std::endl;
	}
}