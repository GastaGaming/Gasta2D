#pragma once
#include "Components.h"
class PositionC : public Component
{
public:
	Vector2D pos;
	PositionC()
	{
		pos.x = 0;
		pos.y = 0;
	}
	PositionC(int x, int y)
	{
		pos.x = x;
		pos.y = y;
	}
	int x() { return pos.x; }
	int y() { return pos.y; }
	void Update() override
	{
		pos.x++;
		pos.y++;
	}
	void setPos(int x, int y)
	{
		pos.x = x;
		pos.y = y;
	}
};