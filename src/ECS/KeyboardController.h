//#include "../Client/Game.h"
#include "ECS.h"
#include "Components.h"
#include <math.h>
#include <vector>
#define PI 3.14159265
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
			Vector2D direction;
			float A;
			switch (Game::event.key.keysym.sym) //Move on statement depending switch key is pressed;
			{
			case SDLK_w:
				//direction.x = cos(transform->angle * 180 / PI);
				//direction.y = sin(transform->angle * 180 / PI);
				//direction.x = cos(transform->angle);
				direction.x = 2 * SDL_cosf((transform->angle - 90) / (180 / PI));
				direction.y = 2 * SDL_sinf((transform->angle - 90) / (180 / PI));
				std::cout << "Andle : " << transform->angle << "\n" << std::endl;
				std::cout << direction << "\n" ;
				transform->velocity.x = direction.x;
				transform->velocity.y = direction.y;
				//transform->velocity.y = -1;
				sprite->Play("Anim2");
				break;
			case SDLK_s:
				direction.x = 2 * SDL_cosf((transform->angle - 90) / (180 / PI));
				direction.y = 2 * SDL_sinf((transform->angle - 90) / (180 / PI));
				std::cout << "Andle : " << transform->angle << "\n" << std::endl;
				std::cout << direction << "\n";
				transform->velocity.x = -direction.x;
				transform->velocity.y = -direction.y;
				//transform->velocity.y = 1;
				sprite->Play("Anim2");
				break;
			case SDLK_d:
				//transform->velocity.x = 1;
				transform->angle += 6;
				std::cout << "Andle : " << transform->angle << "\n" << std::endl;
				direction.x = 0.5 * SDL_cosf((transform->angle - 90) / (180 / PI));
				direction.y = 0.5 * SDL_sinf((transform->angle - 90) / (180 / PI));
				std::cout << "Andle : " << transform->angle << "\n" << std::endl;
				std::cout << direction << "\n";
				transform->velocity.x = direction.x;
				transform->velocity.y = direction.y;
				sprite->Play("Anim2");
				break;
			case SDLK_a:
				//transform->velocity.x = -1;
				transform->angle -= 6;
				std::cout << "Andle : " << transform->angle << "\n" << std::endl;
				direction.x = 0.5 * SDL_cosf((transform->angle - 90) / (180 / PI));
				direction.y = 0.5 * SDL_sinf((transform->angle - 90) / (180 / PI));
				std::cout << "Andle : " << transform->angle << "\n" << std::endl;
				std::cout << direction << "\n";
				transform->velocity.x = direction.x;
				transform->velocity.y = direction.y;
				sprite->Play("Anim2");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
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
				transform->velocity.x = 0;
				transform->velocity.y = 0;
				sprite->Play("Anim0");
				break;
			case SDLK_s:
				transform->velocity.x = 0;
				transform->velocity.y = 0;
				sprite->Play("Anim0");
				break;
			case SDLK_d:
				transform->angle = transform->angle;
				transform->velocity.x = 0;
				transform->velocity.y = 0;
				//transform->velocity.x = 0;
				sprite->Play("Anim0");
				break;
			case SDLK_a:
				transform->angle = transform->angle;
				transform->velocity.x = 0;
				transform->velocity.y = 0;
				//transform->velocity.x = 0;
				sprite->Play("Anim0");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			default:
				break;
			}
		}
	}
};