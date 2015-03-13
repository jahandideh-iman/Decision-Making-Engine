#pragma once

#include "AIComponent.h"
#include <vector>

using namespace std;

class AIManager
{
	typedef vector<AIComponent*> ComponentContainer;

public:
	static AIManager* Get();
	static void Destroy();

	void AddComponent(AIComponent* component);

	void Update(float dt = 0);

	bool isEmpty();

private:
	AIManager();
	~AIManager();
	
private:
	static AIManager* manager;
	ComponentContainer container;
};

