#pragma once
#include "CppUTest/TestHarness.h"
#include "FiniteStateMachineComponent.h"
#include "DMEUtilities.h"
#include "FiniteStateMachineHelperFunctions.h"


class GameObjectMock
{

public:
	void EntryAction(){ isEntryActionCalled = true; }
public:
	bool isEntryActionCalled = false;
};

TEST_GROUP(FiniteStateComponentWithOneState)
{
	FiniteStateMachineComponent* component = nullptr;
	StateName theOnlyStateName = "OnlyState";

	void setup()
	{
		component = new FiniteStateMachineComponent();
	}

	void teardown()
	{
		delete component;
	}

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

	CheckCurrentStateNameIs(component,"");
}

TEST(FiniteStateComponentWithOneState, CurrentStateIsTheOnlyStateAfterFirstUpdate)
{
	AddStateAndSetInitialState(theOnlyStateName);
	component->Update();

	CheckCurrentStateNameIs(component, theOnlyStateName);
}

TEST(FiniteStateComponentWithOneState, StateIsNotChangeAfterTick)
{
	AddStateAndSetInitialState(theOnlyStateName);
	
	CallMultipleUpdate(component, 5);

	CheckCurrentStateNameIs(component, theOnlyStateName);
}



TEST(FiniteStateComponentWithOneState, EntryActionIsExecutedOnFirstUpdate)
{
	bool isExecuted = false;
	AddStateAndSetInitialState(theOnlyStateName);
	SetStateEntryAction(component, theOnlyStateName, "EntryActionName", new OneTimeCalledAction([&]()->void{isExecuted = true; }));

	component->Update();

	CHECK_TRUE(isExecuted);
}

TEST(FiniteStateComponentWithOneState, EntryActionIsExecutedOnlyOnce)
{
	auto actionCallCount = 0u;

	AddStateAndSetInitialState(theOnlyStateName);
	SetStateEntryAction(component, theOnlyStateName, "EntryActionName", new OneTimeCalledAction([&]()->void{ ++actionCallCount; }));

	CallMultipleUpdate(component, 5);

	CHECK_EQUAL(1, actionCallCount);
}

TEST(FiniteStateComponentWithOneState, UpdateActionIsExecutedOnEachUpdate)
{
	auto actionCallCount = 0u;

	AddStateAndSetInitialState(theOnlyStateName);
	SetStateUpdateAction(component, theOnlyStateName, "UpdateActionName", new EveryUpdateCalledAction([&](float dt)->void{ ++actionCallCount; }));

	CallMultipleUpdate(component, 4);

	CHECK_EQUAL(4, actionCallCount);
}

TEST(FiniteStateComponentWithOneState, AcceptMemberFunctionForAction)
{
	GameObjectMock object;
	AddStateAndSetInitialState(theOnlyStateName);
	SetStateEntryAction(component, theOnlyStateName, "EntryActionName", new OneTimeCalledAction(BIND_MEMBER_ACTION(GameObjectMock::EntryAction, &object)));

	component->Update();

	CHECK_TRUE(object.isEntryActionCalled);
}
