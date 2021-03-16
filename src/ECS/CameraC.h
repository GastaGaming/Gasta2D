#pragma once
#include "Components.h"
class CameraC : public Component
{
public:
	Entity* eTarget;
	bool hasTarget = false;
	float camPosX, camPosY = 0;
	CameraC() {}
	~CameraC() {}
	void AddTarget(Entity* inTarget)
	{
		eTarget = inTarget;
		hasTarget = true;
	}
	void Update() override
	{
		camPosX = eTarget->getComponent<TransformC>().position.x + 16;//This is bad ofset based on sprite
		camPosY = eTarget->getComponent<TransformC>().position.y + 16;//This is bad ofset based on sprite
		//std::cout << "Camera pos : " << camPosX << "," << camPosY << std::endl;

	}
};