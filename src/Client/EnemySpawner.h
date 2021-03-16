#pragma once
#include "../ECS/Components.h"
#include "Game.h"
class EnemySpawner : public Component
{
public:
	EnemySpawner();
	~EnemySpawner();
	void Update() override;

private:
	Scene* activeScene;
	int E_MAXCOUNT = 10; //Enemy max count
	int enemyCount = 0;
	std::vector<Entity> enemies;
};

EnemySpawner::EnemySpawner()
{
}

EnemySpawner::~EnemySpawner()
{
}
void EnemySpawner::Update()
{
	//First check if we need to spawn more enemies
	if (enemyCount > E_MAXCOUNT)
	{
		auto& enemy(activeScene->AddEntity());
		enemy.addComponent<TransformC>(0,200);
		enemy.addComponent<SpriteC>("img/Dirt.png");
		enemy.AddGroup(Game::groupEnemies);
		enemies.push_back(enemy);
	}
	//Check if enemy has die so we can spawn more
	for (auto& e : enemies)
	{
		//e->Draw();
	}
}