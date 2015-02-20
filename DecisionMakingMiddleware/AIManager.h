#pragma once

#include "FiniteStateComponent.h"

class AIManager
{
public:
	AIManager();
	~AIManager();

	void AddComponent(FiniteStateComponent component);

	void Update();
};

