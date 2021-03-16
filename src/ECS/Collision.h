#pragma once
#include <SDL.h>

class ColliderC;

struct Collision
{
	//Axis Alling Bounding Box
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
	static bool AABB(const ColliderC& colA, const ColliderC& colB);

};
bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
	if (rectA.x + rectA.w >= rectB.x &&
		rectB.x + rectB.w >= rectA.x &&
		rectA.y + rectA.h >= rectB.y &&
		rectB.y + rectB.h >= rectA.y)
	{
		return true; //Collision
	}
	return false;//No collision
}

bool Collision::AABB(const ColliderC& colA, const ColliderC& colB)
{
	if (AABB(colA.collider, colB.collider))
	{
		//Can hit itself and cannot hit objects with same tag?
		if (colA.entity != colB.entity && colA.tag != colB.tag)
		{
			//std::cout << colA.tag << " hit: " << colB.tag << std::endl;
			return true; //Collision

		}
	}
	return false;//No collision
}