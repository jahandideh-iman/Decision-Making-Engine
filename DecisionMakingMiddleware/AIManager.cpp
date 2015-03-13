#include "AIManager.h"

AIManager* AIManager::manager = nullptr;

AIManager::AIManager()
{
}


AIManager::~AIManager()
{
}

void AIManager::AddComponent(AIComponent* component)
{
	container.push_back(component);
}

void AIManager::Update(float dt)
{
	for (AIComponent* c : container)
		c->Update(dt);
}

AIManager* AIManager::Get()
{
	if (manager == nullptr)
		manager = new AIManager();
	return manager;
}

void AIManager::Destroy()
{
	delete manager;
	manager = nullptr;
}

bool AIManager::isEmpty()
{
	return container.empty();
}
