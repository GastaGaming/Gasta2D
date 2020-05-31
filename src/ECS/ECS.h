#pragma once
#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Scene;
//Each Component has ID
using ComponentID = std::size_t;
using Group = std::size_t;
inline ComponentID getNewTComponentTypeID()
{
	static ComponentID lastID = 0u;// U means unsign
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	//static ComponentID typeID = getComponentTypeID();
	static_assert (std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = getNewTComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32; //Max ammount of component entity can have
constexpr std::size_t maxGroups = 32; //Max Group size, can be used for collision layers and render layers
using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;
	//These are for overwriting
	virtual void Init() {} //For geting other components, etc 
	virtual void Update() {} //For updating component
	virtual void Draw() {} //Drawing if component has image or something visual
	virtual ~Component() {}
};
class Entity
{
private:
	Scene& scene;
	bool active = true; // Can be false so we dont have to update or we can remove it
	std::vector<std::unique_ptr<Component>> components;//Vector has dynamic size
	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;
public:
	Entity(Scene& mScene) : scene(mScene) {} //M means memeber Scene
	void Update() { for (auto& c : components) c->Update(); } //Update componets
	void Draw() { for (auto& c : components) c->Draw(); } //Draw Components
	bool isActive() const { return active; } //Ask if entity is active
	void Destroy() { active = false; } //Destroy will delete entity

	bool HasGroup(Group mGroup){	return groupBitSet[mGroup];	} // Retuns true or false, debendig if certain bit is either 1 or 0}
	void AddGroup(Group mGroup); //{ groupBitSet[mGroup] = true; scene.AddToGroup(this, mGroup); }
	void DeleteGroup(Group mGroup) { groupBitSet[mGroup] = false; }

	template <typename T> bool hasComponent() const //Can be asked does entity have components
	{
		return componetBitset[getComponentID<T>];
	}
	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));
		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;
		//After this we can init component
		c->Init();
		return *c;
	}
	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
	//Example how to use
	//gameobject.getComponent<PositionComponent>().setXpost(25);
};

class Scene
{
private:
	std::vector<std::unique_ptr<Entity>> entities;//Vector so it is dynamic
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;//We have goyp array of grouped entities, entities in a group can collide or render in order
public:
	void Update()
	{
		for (auto& e : entities) e->Update();
	}
	void Draw()
	{
		for (auto& e : entities) e->Draw();
	}
	void Refresh()
	{
		for (auto i(0u); i < maxGroups; i++)//This will take removing entities from group
		{
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity)
			{
				return !mEntity->isActive() || !mEntity->HasGroup(i);
			}),
				std::end(v));
		}
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
		{
			return !mEntity->isActive();
		}),
			std::end(entities));
	}

	void AddToGroup(Entity* mEntity, Group mGroup) //Add entitty to group
	{
		groupedEntities[mGroup].emplace_back(mEntity);
	}
	std::vector<Entity*>& getGroup(Group mGroup)// Gives list of entities inside a group
	{
		return groupedEntities[mGroup]; 
	}

	Entity& AddEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};

void Entity::AddGroup(Group mGroup)
{
	groupBitSet[mGroup] = true; 
	scene.AddToGroup(this, mGroup);
}