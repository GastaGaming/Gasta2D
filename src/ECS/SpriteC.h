#pragma once
#include "Components.h"
#include "SDL.h"
#include "../Client/TextureLoader.h"
#include <map>
struct Animation
{
	int index;
	int frames;
	int speed;
	Animation() {}
	Animation(int i, int f, int s)
	{
		index = i;
		frames = f;
		speed = s;
	}
};
class SpriteC : public Component
{
private:
	TransformC* transform;
	CameraC* camera;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	bool animated = false;
	int frames = 0;
	int speed = 100; // This value is dealy between frames !!!!! in ms

public:
	int animIndex = 0; // Needs to 0 if we dont have animations
	std::map<const char*, Animation> animations; //This holds our animations

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteC() = default;
	SpriteC(const char* path)
	{
		SetTexture(path);
	}
	SpriteC(const char* path, bool isAnimated)
	{
		animated = true;

		Animation idle = Animation(0, 3, 200);
		Animation walk = Animation(1, 8, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);
		Play("Idle");
		SetTexture(path);
	}
	SpriteC(const char* path, bool isAnimated, int frames)
	{
		animated = true;
		Animation idle = Animation(0, frames, 500);
		animations.emplace("Idle", idle);
		Play("Idle");
		SetTexture(path);
	}
	~SpriteC()
	{
		SDL_DestroyTexture(texture);
	}
	void SetTexture(const char* path)
	{
		texture = TextureLoader::LoadTexture(path);
	}
	void Init() override
	{
		transform = &entity->getComponent<TransformC>();
		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}
	void Update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;
		destRect.x = static_cast<int>(transform->position.x - Game::camera->camPosX);
		destRect.y = static_cast<int>(transform->position.y - Game::camera->camPosY);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
		//if(Game::activeCamera == true)
		//{
		//	/*destRect.x = static_cast<int>(transform->position.x - cc.cameraRect.x);
		//	destRect.y = static_cast<int>(transform->position.y - cc.cameraRect.y);
		//	destRect.w = transform->width * transform->scale;
		//	destRect.h = transform->height * transform->scale;*/
		//}
		//else
		//{
		//	destRect.x = static_cast<int>(transform->position.x);
		//	destRect.y = static_cast<int>(transform->position.y);
		//	destRect.w = transform->width * transform->scale;
		//	destRect.h = transform->height * transform->scale;
		//}
	}
	void Draw() override
	{
		TextureLoader::Draw(texture, srcRect, destRect, spriteFlip);
	}
	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;

	}
};