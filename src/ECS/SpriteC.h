#pragma once
#include "Components.h"
#include "SDL.h"
#include "../Client/TextureLoader.h"
#include <map>
#include <string>
#include <sstream> 
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
	float angle = 0;
	bool animated = false;
	int frames = 0;
	int speed = 100; // This value is dealy between frames !!!!! in ms

public:
	int animIndex = 0; // Needs to 0 if we dont have animations
	std::map<std::string, Animation> animations;
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteC() = default;
	SpriteC(const char* path)
	{
		SetTexture(path);
	}
	SpriteC(const char* path, bool isAnimated)
	{
		animated = true;

		Animation idle = Animation(0, 4, 200);
		Animation walk = Animation(1, 4, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);
		Play("Idle");
		SetTexture(path);
	}
	SpriteC(const char* path, bool isAnimated, int frames)
	{
		animated = isAnimated;
		Animation idle = Animation(0, frames, 500);
		animations.emplace("Idle", idle);
		Play("Idle");
		SetTexture(path);
	}
	SpriteC(const char* path, bool isAnimated,
		int numOfAnimations,
		std::vector<int> framesInAnimation,
		std::vector<int> delayPerAnimation)
	{
		animated = isAnimated;
		for (int i = 0; i < numOfAnimations; i++)
		{
			Animation anim = Animation(i, framesInAnimation[i], delayPerAnimation[i]);
			char c = (char)i;
			std::string animName = "Anim" + std::to_string(i);
			std::cout << animName << "\n";
			animations.emplace(animName, anim);
		}
		Play("Anim0");
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
		//Maybe I should check if user want's a camera
		srcRect.y = animIndex * transform->height;
		destRect.x = static_cast<int>(transform->position.x - Game::camera->camPosX + (1280/2));
		destRect.y = static_cast<int>(transform->position.y - Game::camera->camPosY + (720/2));
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
		angle = transform->angle;
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
		TextureLoader::Draw(texture, srcRect, destRect, angle, spriteFlip);
	}
	/*void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;

	}*/
	void Play(std::string animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};