#include "CppUTest/TestHarness.h"
#include "FiniteStateComponent.h"

TEST_GROUP(FiniteStateComponentWithMultipleStates)
{
	FiniteStateComponent component;
};

TEST(FiniteStateComponentWithMultipleStates, HasTheAddedStates)
{
	component.AddState("State1");
	component.AddState("State2");

	CHECK_TRUE(component.HasState("State1"));
	CHECK_TRUE(component.HasState("State2"));
}