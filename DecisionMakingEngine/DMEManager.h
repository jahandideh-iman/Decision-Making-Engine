#pragma once

#include "DMEComponent.h"
#include <vector>

using namespace std;

class DMEManager
{
	typedef vector<DMEComponent*> ComponentContainer;

public:
	static DMEManager* Get();
	static void Destroy();

	void AddComponent(DMEComponent* component);

	void Update(float dt = 0);

	bool isEmpty();

private:
	DMEManager();
	~DMEManager();
	
private:
	static DMEManager* manager;
	ComponentContainer container;
};

