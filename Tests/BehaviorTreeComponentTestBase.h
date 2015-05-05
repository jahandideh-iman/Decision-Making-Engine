#pragma once

#include "CppUTest/TestHarness.h"
#include "BehaviorTreeComponent.h"

TEST_BASE(BehaviorTreeComponentTestBase)
{
public:
	BehaviorTreeComponent *component;
	void setup()
	{
		component = new BehaviorTreeComponent();
	}

	void teardown()
	{
		delete component;
	}

	void CallMultipleUpdate(unsigned numberOfTimes)
	{
		for (unsigned i = 0; i < numberOfTimes; ++i)
			component->Update(0.5);
	}
};