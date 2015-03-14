#include "DMEManager.h"

DMEManager* DMEManager::manager = nullptr;

DMEManager::DMEManager()
{
}


DMEManager::~DMEManager()
{
}

void DMEManager::AddComponent(DMEComponent* component)
{
	container.push_back(component);
}

void DMEManager::Update(float dt)
{
	for (DMEComponent* c : container)
		c->Update(dt);
}

DMEManager* DMEManager::Get()
{
	if (manager == nullptr)
		manager = new DMEManager();
	return manager;
}

void DMEManager::Destroy()
{
	delete manager;
	manager = nullptr;
}

bool DMEManager::isEmpty()
{
	return container.empty();
}
