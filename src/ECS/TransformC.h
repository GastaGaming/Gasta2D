/**
 * This component is used for perfomming setting entitys position, rotation and scale
 */
#pragma once
#include "Components.h"
#include "Vector2D.h"
class TransformC : public Component
{
public:
	Vector2D position;
	Vector2D velocity;

	int height = 32;//This should be in the spriteC
	int width = 32;//This should be in the spriteC
	int scale = 1;

	int speed = 3;
	TransformC()
	{
		position.Zero();
		scale = 1;
	}
	TransformC(int sc)
	{
		position.Zero();
		scale = sc;
	}
	TransformC(float x, float y)
	{
		position.x = x;
		position.y = y;
		scale = 1;
	}
	TransformC(float x, float y, int h, int w, int s)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = s;
	}
	void Init() override
	{
		velocity.Zero();
		velocity.Zero();
	}
	void Update() override
	{
		//pos.x++;
		//pos.y++;
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;

	}
	void setPos(int x, int y)
	{
		position.x = x;
		position.y = y;
	}
};