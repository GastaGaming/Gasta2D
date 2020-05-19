#pragma once
#include "Components.h"
#include "SDL.h"
#include "../Client/TextureLoader.h"
class SpriteC : public Component
{
private:
	PositionC* position;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
public:
	SpriteC() = default;
	SpriteC(const char* path)
	{
		SetTexture(path);
	}
	void SetTexture(const char* path)
	{
		texture = TextureLoader::LoadTexture(path);
	}
	void Init() override
	{
		position = &entity->getComponent<PositionC>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;
		destRect.w = destRect.h = 64;
	}
	void Update() override
	{
		destRect.x = position->x();
		destRect.y = position->y();
	}
	void Draw() override
	{
		TextureLoader::Draw(texture, srcRect, destRect);
	}
};