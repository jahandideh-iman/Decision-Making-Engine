#pragma once
#include "CppUTest/TestHarness.h"
#include "FiniteStateMachine/FiniteStateMachineComponent.h"
#include "FiniteStateComponentTestBase.h"

using DME::StateName;

TEST_GROUP_BASE(FiniteStateComponentWithMultipleStates, FiniteStateComponentTestBase)
{

	StateName firstStateName = "firstState";
	StateName secondStateName = "secondState";

	void setup()
	{
		FiniteStateComponentTestBase::setup();
		component->AddState(firstStateName);
		component->AddState(secondStateName);
		component->SetInitialState(firstStateName);
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
	SetTransition(firstStateName, secondStateName, "ConditionOne", InterfaceFactory::CreateCondition([]()->bool{return false; }));

	//On first Update component will go to initial state
	component->Update();
	component->Update();

	CheckCurrentStateNameIs(firstStateName);
}


TEST(FiniteStateComponentWithMultipleStates, StateIsChangedWhenTransitionConditionIsMet)
{
	SetTransition(firstStateName, secondStateName, "ConditionOne", InterfaceFactory::CreateCondition([]()->bool{return true; }));

	//On first Update component will go to initial state
	component->Update();
	component->Update();

	CheckCurrentStateNameIs( secondStateName);
}

TEST(FiniteStateComponentWithMultipleStates, StateIsSetToInitialStateOnFirstUpdate)
{
	SetTransition(firstStateName, secondStateName, "ConditionOne", InterfaceFactory::CreateCondition([]()->bool{return true; }));

	//On first Update component will go to initial state
	component->Update();
	CheckCurrentStateNameIs(firstStateName);
}

TEST(FiniteStateComponentWithMultipleStates, StateIsNotChangedAfterTransition)
{
	SetTransition(firstStateName, secondStateName, "ConditionOne", InterfaceFactory::CreateCondition([]()->bool{return true; }));

	//On first Update component will go to initial state
	component->Update();
	CallMultipleUpdate(5);

	CheckCurrentStateNameIs(secondStateName);
}

TEST(FiniteStateComponentWithMultipleStates, EntryActionForDestinationIsCalledOnStateTransition)
{
	bool isExecuted = false;

	SetTransition(firstStateName, secondStateName, "ConditionOne", InterfaceFactory::CreateCondition([]()->bool{return true; }));
	SetStateEntryAction(secondStateName, "SecondEntryAction", InterfaceFactory::CreateAction([&]()->void{isExecuted = true; }));

	//On first Update component will go to initial state
	component->Update();
	component->Update();

	CHECK_TRUE(isExecuted);
}

TEST(FiniteStateComponentWithMultipleStates, ExistActionForSourceIsCalledOnStateTransition)
{
	bool isExecuted = false;

	SetTransition(firstStateName, secondStateName, "ConditionOne", InterfaceFactory::CreateCondition([]()->bool{return true; }));
	SetStateExitAction(firstStateName, "FirstExitAction", InterfaceFactory::CreateAction([&]()->void{isExecuted = true; }));

	//On first Update component will go to initial state
	component->Update();
	component->Update();

	CHECK_TRUE(isExecuted);
}

TEST(FiniteStateComponentWithMultipleStates, UpdateActionIsCallOnEachUpdateAfterTransition)
{
	auto callCount = 0u;

	SetTransition(firstStateName, secondStateName, "ConditionOne", InterfaceFactory::CreateCondition([]()->bool{return true; }));
	SetStateUpdateAction(secondStateName, "SecondUpdateAction", InterfaceFactory::CreateUpdateAction([&](float dt)->void{++callCount; }));

	//On first Update component will go to initial state
	component->Update();
	CallMultipleUpdate(5);

	CHECK_EQUAL(5,callCount);
}

