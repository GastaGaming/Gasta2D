//#include "../Client/Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformC* transform;
	SpriteC* sprite;
	CameraC* camera;
	void Init() override
	{
		transform = &entity->getComponent<TransformC>();
		sprite = &entity->getComponent<SpriteC>();
	}
	void Update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym) //Move on statement depending switch key is pressed;
			{
			case SDLK_w:
				transform->velocity.y = -1;
				//sprite->Play("Walk");
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				//sprite->Play("Walk");
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				//sprite->Play("Walk");
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				//sprite->Play("Walk");
				//sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
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
				//sprite->Play("Idle");
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				//sprite->Play("Idle");
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				//sprite->Play("Idle");
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				//sprite->Play("Idle");
				//sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			default:
				break;
			}
		}
	}
};