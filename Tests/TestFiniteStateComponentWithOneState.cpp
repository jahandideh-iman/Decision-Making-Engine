#pragma once
#include "CppUTest/TestHarness.h"
#include "FiniteStateMachineComponent.h"
#include "DMEUtilities.h"
#include "FiniteStateComponentTestBase.h"


class GameObjectMock
{

public:
	void EntryAction(){ isEntryActionCalled = true; }
public:
	bool isEntryActionCalled = false;
};

TEST_GROUP_BASE(FiniteStateComponentWithOneState,FiniteStateComponentTestBase)
{
	StateName theOnlyStateName = "OnlyState";

	void AddStateAndSetInitialState(StateName stateName)
	{
		component->AddState(stateName);
		component->SetInitialState(stateName);
	}

};

TEST(FiniteStateComponentWithOneState, HasNoStateOnCreation)
{
	CHECK_TRUE(component->HasNoState());
}

TEST(FiniteStateComponentWithOneState, HasStatesAfterAddingState)
{
	component->AddState(theOnlyStateName);

	CHECK_FALSE(component->HasNoState());
}

TEST(FiniteStateComponentWithOneState, CurrentStateIsEmptyOnCreation)
{
	component->AddState(theOnlyStateName);

	CheckCurrentStateNameIs("");
}

TEST(FiniteStateComponentWithOneState, CurrentStateIsTheOnlyStateAfterFirstUpdate)
{
	AddStateAndSetInitialState(theOnlyStateName);
	component->Update();

	CheckCurrentStateNameIs(theOnlyStateName);
}

TEST(FiniteStateComponentWithOneState, StateIsNotChangeAfterTick)
{
	AddStateAndSetInitialState(theOnlyStateName);
	
	CallMultipleUpdate(5);

	CheckCurrentStateNameIs(theOnlyStateName);
}



TEST(FiniteStateComponentWithOneState, EntryActionIsExecutedOnFirstUpdate)
{
	bool isExecuted = false;
	AddStateAndSetInitialState(theOnlyStateName);
	SetStateEntryAction(theOnlyStateName, "EntryActionName", new OneTimeCalledAction([&]()->void{isExecuted = true; }));

	component->Update();

	CHECK_TRUE(isExecuted);
}

TEST(FiniteStateComponentWithOneState, EntryActionIsExecutedOnlyOnce)
{
	auto actionCallCount = 0u;

	AddStateAndSetInitialState(theOnlyStateName);
	SetStateEntryAction(theOnlyStateName, "EntryActionName", new OneTimeCalledAction([&]()->void{ ++actionCallCount; }));

	CallMultipleUpdate(5);

	CHECK_EQUAL(1, actionCallCount);
}

TEST(FiniteStateComponentWithOneState, UpdateActionIsExecutedOnEachUpdate)
{
	auto actionCallCount = 0u;

	AddStateAndSetInitialState(theOnlyStateName);
	SetStateUpdateAction(theOnlyStateName, "UpdateActionName", new EveryUpdateCalledAction([&](float dt)->void{ ++actionCallCount; }));

	CallMultipleUpdate(4);

	CHECK_EQUAL(4, actionCallCount);
}

TEST(FiniteStateComponentWithOneState, AcceptMemberFunctionForAction)
{
	GameObjectMock object;
	AddStateAndSetInitialState(theOnlyStateName);
	SetStateEntryAction(theOnlyStateName, "EntryActionName", new OneTimeCalledAction(BIND_MEMBER_ACTION(GameObjectMock::EntryAction, &object)));

	component->Update();

	CHECK_TRUE(object.isEntryActionCalled);
}
