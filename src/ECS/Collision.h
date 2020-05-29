#pragma once
#include <SDL.h>
struct Collision
{
	//Axis Alling Bounding Box
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
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