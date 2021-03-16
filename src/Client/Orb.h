#pragma once
#include "../ECS/Components.h"
class Orb : public Component
{
public:
	TransformC* transform;
	Vector2D direction;
	int ORBSPEED = 1;
	Orb()
	{
	}
	~Orb(){}
	void Init() override;
	void Update() override;
private:
};
void Orb::Init()
{
	transform = &entity->getComponent<TransformC>();
	int result = 0 + (rand() & 360);
	direction.x = ORBSPEED * SDL_cosf((result - 90) / (180 / PI));
	direction.y = ORBSPEED * SDL_sinf((result - 90) / (180 / PI));
	transform->velocity.x = direction.x;
	transform->velocity.y = direction.y;
}
void Orb::Update()
{
	//Generate random direction and go there
	//transform->velocity.x = direction.x;
	//transform->velocity.y = direction.y;
}