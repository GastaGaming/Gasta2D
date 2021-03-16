#pragma once
#include "ECS.h"
#include "TransformC.h"

class TileC : public Component
{
public:
	TransformC* transform;
	SpriteC* sprite;

	SDL_Rect tileRect;
	int tileID;
	char* path;
	TileC() = default;
	~TileC(){}
	int sc = 1;
	TileC(int x, int y, int w, int h, int id, int scale)
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;
		sc = scale;
		switch (tileID)
		{
		case 0:
			path = "img/SpacePinkBlock.png";
			break;
		case 1:
			path = "img/SpaceGreenBlock.png";
			break;
		case 2:
			path = "img/SpaceBG.png";
			break;
		default:
			break;
		}

	}

	void Init() override
	{
		entity->addComponent<TransformC>(tileRect.x, tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformC>();
		transform->scale = sc;
		
		entity->addComponent<SpriteC>(path, true, 6);
		sprite = &entity->getComponent<SpriteC>();
	}
};