#pragma once
#include "CppUTest/TestHarness.h"
#include "FiniteStateMachineComponent.h"
#include "FiniteStateMachineHelperFunctions.h"

TEST_GROUP(FiniteStateComponentWithMultipleStates)
{
	FiniteStateMachineComponent* component = nullptr;
	StateName firstStateName = "firstState";
	StateName secondStateName = "secondState";

	void setup()
	{
		component = new FiniteStateMachineComponent();
		component->AddState(firstStateName);
		component->AddState(secondStateName);
		component->SetInitialState(firstStateName);
	}

	void teardown()
	{
		delete component;
	}

};

TEST(FiniteStateComponentWithMultipleStates, HasTheAddedStates)
{
	CHECK_TRUE(component->HasState(firstStateName));
	CHECK_TRUE(component->HasState(secondStateName));
}

TEST(FiniteStateComponentWithMultipleStates, CurrentStateIsTheInitialStateOnFirstUpdate)
{
	component->Update();
	CHECK_EQUAL(firstStateName, component->GetCurrentStateName());
}

TEST(FiniteStateComponentWithMultipleStates, StateIsNotChangedWhenTransitionConditionIsNotMet)
{
	SetTransition(component,firstStateName, secondStateName, "ConditionOne" ,new Condition([]()->bool{return false; }));

	//On first Update component will go to initial state
	component->Update();
	component->Update();

	CheckCurrentStateNameIs(component, firstStateName);
}


TEST(FiniteStateComponentWithMultipleStates, StateIsChangedWhenTransitionConditionIsMet)
{
	SetTransition(component ,firstStateName, secondStateName,"ConditionOne" ,new Condition([]()->bool{return true; }));

	//On first Update component will go to initial state
	component->Update();
	component->Update();

	CheckCurrentStateNameIs(component, secondStateName);
}

TEST(FiniteStateComponentWithMultipleStates, StateIsSetToInitialStateOnFirstUpdate)
{
	SetTransition(component, firstStateName, secondStateName, "ConditionOne", new Condition([]()->bool{return true; }));

	//On first Update component will go to initial state
	component->Update();
	CheckCurrentStateNameIs(component, firstStateName);
}

TEST(FiniteStateComponentWithMultipleStates, StateIsNotChangedAfterTransition)
{
	SetTransition(component, firstStateName, secondStateName, "ConditionOne", new Condition([]()->bool{return true; }));

	//On first Update component will go to initial state
	component->Update();
	CallMultipleUpdate(component, 5);

	CheckCurrentStateNameIs(component, secondStateName);
}

TEST(FiniteStateComponentWithMultipleStates, EntryActionForDestinationIsCalledOnStateTransition)
{
	bool isExecuted = false;

	SetTransition(component, firstStateName, secondStateName, "ConditionOne", new Condition([]()->bool{return true; }));
	SetStateEntryAction(component, secondStateName, "SecondEntryAction" , new OneTimeCalledAction([&]()->void{isExecuted = true; }));

	//On first Update component will go to initial state
	component->Update();
	component->Update();

	CHECK_TRUE(isExecuted);
}

TEST(FiniteStateComponentWithMultipleStates, ExistActionForSourceIsCalledOnStateTransition)
{
	bool isExecuted = false;

	SetTransition(component, firstStateName, secondStateName, "ConditionOne", new Condition([]()->bool{return true; }));
	SetStateExitAction(component, firstStateName, "FirstExitAction" ,new OneTimeCalledAction([&]()->void{isExecuted = true; }));

	//On first Update component will go to initial state
	component->Update();
	component->Update();

	CHECK_TRUE(isExecuted);
}

TEST(FiniteStateComponentWithMultipleStates, UpdateActionIsCallOnEachUpdateAfterTransition)
{
	auto callCount = 0u;

	SetTransition(component, firstStateName, secondStateName, "ConditionOne", new Condition([]()->bool{return true; }));
	SetStateUpdateAction(component, secondStateName, "SecondUpdateAction", new EveryUpdateCalledAction([&](float dt)->void{++callCount; }));

	//On first Update component will go to initial state
	component->Update();
	CallMultipleUpdate(component, 5);

	CHECK_EQUAL(5,callCount);
}

