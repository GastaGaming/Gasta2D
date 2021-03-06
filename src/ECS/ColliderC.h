#include "Components.h"
class ColliderC : public Component
{
public:
	SDL_Rect collider;
	std::string tag;//Futue to tag entities

	TransformC* transform;
	ColliderC(std::string t)
	{
		tag = t;
	}
	void Init() override
	{
		//if (!entity->hasComponent<TransformC>())//Check if entity has tranform component if not lets create one
		//{
		//	entity->addComponent<TransformC>();
		//}
		transform = &entity->getComponent<TransformC>();

		Game::colliders.push_back(this);
	}

	void Update() override
	{
		if (tag != "static")
		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}
	}
};