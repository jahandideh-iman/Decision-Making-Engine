#include "CppUTest/TestHarness.h"
#include "FiniteStateMachineComponent.h"
#include "DMEUtilities.h"


class GameObjectMock
{

public:
	void EntryAction(){ isEntryActionCalled = true; }
public:
	bool isEntryActionCalled = false;
};

TEST_GROUP(FiniteStateComponentWithOneState)
{
	FiniteStateMachineComponent component;
	StateName theOnlyState = "OnlyState";

	void CallMultipleUpdate(unsigned numberOfTimes)
	{
		for (unsigned i = 0; i < numberOfTimes; ++i)
			component.Update();
	}

	void AddStateAndSetInitialState(StateName stateName)
	{
		component.AddState(stateName);
		component.SetInitialState(stateName);
	}

	void CheckCurrentStateNameIs(StateName stateName)
	{
		CHECK_EQUAL(stateName, component.GetCurrentStateName());
	}

};

TEST(FiniteStateComponentWithOneState, HasNoStateOnCreation)
{
	CHECK_TRUE(component.HasNoState());
}

TEST(FiniteStateComponentWithOneState, HasStatesAfterAddingState)
{
	component.AddState(theOnlyState);

	CHECK_FALSE(component.HasNoState());
}

TEST(FiniteStateComponentWithOneState, CurrentStateIsEmptyOnCreation)
{
	component.AddState(theOnlyState);

	CheckCurrentStateNameIs("");
}

TEST(FiniteStateComponentWithOneState, CurrentStateIsTheOnlyStateAfterFirstUpdate)
{
	AddStateAndSetInitialState(theOnlyState);
	component.Update();

	CheckCurrentStateNameIs(theOnlyState);
}

TEST(FiniteStateComponentWithOneState, StateIsNotChangeAfterTick)
{
	AddStateAndSetInitialState(theOnlyState);
	
	CallMultipleUpdate(5);

	CheckCurrentStateNameIs(theOnlyState);
}



TEST(FiniteStateComponentWithOneState, EntryActionIsExecutedOnFirstUpdate)
{
	bool isExecuted = false;
	AddStateAndSetInitialState(theOnlyState);
	component.SetStateEntryAction(theOnlyState, [&]()->void{isExecuted = true; });

	component.Update();

	CHECK_TRUE(isExecuted);
}

TEST(FiniteStateComponentWithOneState, EntryActionIsExecutedOnlyOnce)
{
	auto actionCallCount = 0u;
	auto arbitrary = 4u;

	AddStateAndSetInitialState(theOnlyState);
	component.SetStateEntryAction(theOnlyState, [&]()->void{ ++actionCallCount; });

	CallMultipleUpdate(arbitrary);

	CHECK_EQUAL(1, actionCallCount);
}

TEST(FiniteStateComponentWithOneState, UpdateActionIsExecutedOnEachUpdate)
{
	auto actionCallCount = 0u;
	auto numberOfUpdateCalls = 4u;

	AddStateAndSetInitialState(theOnlyState);
	component.SetStateUpdateAction(theOnlyState, [&](float dt)->void{ ++actionCallCount; });

	CallMultipleUpdate(numberOfUpdateCalls);

	CHECK_EQUAL(numberOfUpdateCalls, actionCallCount);
}

TEST(FiniteStateComponentWithOneState, AcceptMemberFunctionForAction)
{
	GameObjectMock object;
	AddStateAndSetInitialState(theOnlyState);
	component.SetStateEntryAction(theOnlyState, BIND_MEMBER_ACTION(GameObjectMock::EntryAction, &object));

	component.Update();

	CHECK_TRUE(object.isEntryActionCalled);
}
