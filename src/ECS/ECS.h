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

//Each Component has ID
using ComponentID = std::size_t;
inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32; //Max ammount of component entity can have
using ComponentBitSet = std::bitset<maxComponents>;
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
	bool active = true; // Can be false so we dont have to update or we can remove it
	std::vector<std::unique_ptr<Component>> components;//Vector has dynamic size
	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
public:
	void Update() { for (auto& c : components) c->Update(); } //Update componets
	void Draw() { for (auto& c : components) c->Draw(); } //Draw Components
	bool isActive() const { return active; } //Ask if entity is active
	void Destroy() { active = false; } //Destroy will delete entity
	template <typename T> bool hasComponent() const //Can be asked does enty have components
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
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
		{
			return !mEntity->isActive();
		}),
			std::end(entities));
	}
	Entity& AddEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};