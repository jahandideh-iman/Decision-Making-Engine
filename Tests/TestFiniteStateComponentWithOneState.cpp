#include "CppUTest/TestHarness.h"
#include "AIManager.h"
#include "FiniteStateComponent.h"

TEST_GROUP(FiniteStateComponentWithOneState)
{
	FiniteStateComponent component;
	StateName theOnlyState = "OnlyState";

	void CallMultipleUpdate(unsigned numberOfTimes)
	{
		for (unsigned i = 0; i < numberOfTimes; ++i)
			component.Update();
	}

};

TEST(FiniteStateComponentWithOneState, StateIsEmptyOnCreation)
{
	CHECK_EQUAL("", component.GetState());
}

TEST(FiniteStateComponentWithOneState, StateDoesNotChangeAfterTick)
{
	component.AddState(theOnlyState);
	
	component.Update();

	CHECK_EQUAL(theOnlyState, component.GetCurrentState());
}

TEST(FiniteStateComponentWithOneState, CurrentStateIsEmptyOnCreation)
{
	component.AddState(theOnlyState);

	CHECK_EQUAL("", component.GetCurrentState());
}

TEST(FiniteStateComponentWithOneState, ExecuteTheEntryActionOnFirstUpdate)
{
	bool isExecuted = false;
	component.AddState(theOnlyState);
	component.SetStateEntryAction(theOnlyState, [&]()->void{isExecuted = true; });

	component.Update();

	CHECK_TRUE(isExecuted);
}

TEST(FiniteStateComponentWithOneState, ExecuteTheEntryActionOnlyOnce)
{
	auto actionCallCount = 0u;
	auto arbitrary = 4u;

	component.AddState(theOnlyState);
	component.SetStateEntryAction(theOnlyState, [&]()->void{ ++actionCallCount; });

	CallMultipleUpdate(arbitrary);

	CHECK_EQUAL(1, actionCallCount);
}

TEST(FiniteStateComponentWithOneState, ExecuteTheStateActionOnEachUpdate)
{
	auto actionCallCount = 0u;
	auto numberOfUpdateCalls = 4u;

	component.AddState(theOnlyState);
	component.SetStateAction(theOnlyState, [&]()->void{ ++actionCallCount; });

	CallMultipleUpdate(numberOfUpdateCalls);

	CHECK_EQUAL(numberOfUpdateCalls, actionCallCount);
}
