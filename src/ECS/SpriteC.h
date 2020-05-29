#pragma once
#include "Components.h"
#include "SDL.h"
#include "../Client/TextureLoader.h"
class SpriteC : public Component
{
private:
	TransformC* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
public:
	SpriteC() = default;
	SpriteC(const char* path)
	{
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
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}
	void Draw() override
	{
		TextureLoader::Draw(texture, srcRect, destRect);
	}
};