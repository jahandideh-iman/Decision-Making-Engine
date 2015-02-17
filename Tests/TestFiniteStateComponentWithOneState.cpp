#include "CppUTest/TestHarness.h"
#include "AIManager.h"
#include "FiniteStateComponent.h"

TEST_GROUP(FiniteStateComponentWithOneState)
{
	AIManager manager;
	FiniteStateComponent component;
	void setup()
	{
		manager.AddComponent(component);
	}
};

TEST(FiniteStateComponentWithOneState, StateIsEmptyOnCreation)
{
	CHECK_EQUAL("", component.GetState());
}

TEST(FiniteStateComponentWithOneState, StateDoesNotChangeAfterTick)
{
	component.AddState("ArbiteraryState");
	
	manager.Tick();

	CHECK_EQUAL("ArbiteraryState", component.GetState());
}
