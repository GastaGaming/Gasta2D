#pragma once
#include "../ECS/Components.h"
#include "Orb.h"
//#include "Game.h"
class OrbSpawner : public Component
{
public:
	OrbSpawner(int maxOrbs, Scene& s) 
	{ 
		MaxNumberOfOrbs = maxOrbs; 
		activeScene = &s; 
	}
	~OrbSpawner() {};
	void Update() override;
	std::vector<Entity*> orbs;
private:
	int MaxNumberOfOrbs = 20;
	Scene* activeScene;
};

void OrbSpawner::Update()
{
	if (orbs.size() < MaxNumberOfOrbs)
	{
		//std::cout << "PASKAA";
		auto& orb(activeScene->AddEntity());
		int ofset = 32 * orbs.size();
		orb.addComponent<TransformC>(0 + ofset + 200, 0 + ofset + 200, 2);
		orb.addComponent<SpriteC>("img/OrbGreen.png", true);
		orb.addComponent<ColliderC>("orb");
		orb.addComponent<Orb>();
		orb.AddGroup(Game::groupOrbs);
		orbs.push_back(&orb);
	}
}