//#include "../Client/Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformC* transform;
	void Init() override
	{
		transform = &entity->getComponent<TransformC>();
	}
	void Update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym) //Move on statement depending switch key is pressed;
			{
			case SDLK_w:
				transform->velocity.y = -1;
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				break;
			default:
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym) //Move on statement depending switch key is pressed;
			{
			case SDLK_w:
				transform->velocity.y = 0;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				break;
			default:
				break;
			}
		}
	}
};