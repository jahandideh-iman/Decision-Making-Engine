#include "CppUTest/TestHarness.h"
#include "FiniteStateMachineComponent.h"

TEST_GROUP(FiniteStateComponentWithMultipleStates)
{
	FiniteStateMachineComponent component;
	StateName firstState = "firstState";
	StateName secondState = "secondState";

	void setup()
	{
		component.AddState(firstState);
		component.AddState(secondState);
		component.SetInitialState(firstState);
	}

	void CheckCurrentStateNameIs(StateName stateName)
	{
		CHECK_EQUAL(stateName, component.GetCurrentStateName());
	}

	void CallMultipleUpdate(unsigned numberOfTimes)
	{
		for (unsigned i = 0; i < numberOfTimes; ++i)
			component.Update();
	}

	void SetStateEntryAction(StateName stateName, ActionName actionName, DME::Action action)
	{
		component.AddAction(actionName);
		component.SetActionMethod(actionName, action);
		component.SetStateEntryAction(stateName, actionName);
	}

	void SetStateUpdateAction(StateName stateName, ActionName actionName, DME::UpdateAction action)
	{
		component.AddAction(actionName);
		component.SetUpdateActionMethod(actionName, action);
		component.SetStateUpdateAction(stateName, actionName);
	}

	void SetStateExitAction(StateName stateName, ActionName actionName, DME::Action action)
	{
		component.AddAction(actionName);
		component.SetActionMethod(actionName, action);
		component.SetStateExitAction(stateName, actionName);
	}


};

TEST(FiniteStateComponentWithMultipleStates, HasTheAddedStates)
{
	CHECK_TRUE(component.HasState(firstState));
	CHECK_TRUE(component.HasState(secondState));
}

TEST(FiniteStateComponentWithMultipleStates, CurrentStateIsTheInitialStateOnFirstUpdate)
{
	component.Update();

	CheckCurrentStateNameIs(firstState);
}

TEST(FiniteStateComponentWithMultipleStates, StateIsNotChangedWhenTransitionConditionIsNotMet)
{
	component.SetTransition(firstState, secondState, []()->bool{return false; });

	//On first Update component will go to initial state
	component.Update();
	component.Update();

	CheckCurrentStateNameIs(firstState);
}


TEST(FiniteStateComponentWithMultipleStates, StateIsChangedWhenTransitionConditionIsMet)
{
	component.SetTransition(firstState, secondState, []()->bool{return true; });

	//On first Update component will go to initial state
	component.Update();
	component.Update();

	CheckCurrentStateNameIs(secondState);
}

TEST(FiniteStateComponentWithMultipleStates, StateIsSetToInitialStateOnFirstUpdate)
{
	component.SetTransition(firstState, secondState, []()->bool{return true; });

	//On first Update component will go to initial state
	component.Update();
	CheckCurrentStateNameIs(firstState);
}

TEST(FiniteStateComponentWithMultipleStates, StateIsNotChangedAfterTransition)
{
	component.SetTransition(firstState, secondState, []()->bool{return true; });

	//On first Update component will go to initial state
	component.Update();
	CallMultipleUpdate(5);

	CheckCurrentStateNameIs(secondState);
}

TEST(FiniteStateComponentWithMultipleStates, EntryActionForDestinationIsCalledOnStateTransition)
{
	bool isExecuted = false;

	component.SetTransition(firstState, secondState, []()->bool{return true; });
	SetStateEntryAction(secondState, "SecondEntryAction" , [&]()->void{isExecuted = true; });

	//On first Update component will go to initial state
	component.Update();
	component.Update();

	CHECK_TRUE(isExecuted);
}

TEST(FiniteStateComponentWithMultipleStates, ExistActionForSourceIsCalledOnStateTransition)
{
	bool isExecuted = false;

	component.SetTransition(firstState, secondState, []()->bool{return true; });
	SetStateExitAction(firstState, "FirstExitAction" ,[&]()->void{isExecuted = true; });

	//On first Update component will go to initial state
	component.Update();
	component.Update();

	CHECK_TRUE(isExecuted);
}

TEST(FiniteStateComponentWithMultipleStates, UpdateActionIsCallOnEachUpdateAfterTransition)
{
	auto callCount = 0u;

	component.SetTransition(firstState, secondState, []()->bool{return true; });
	SetStateUpdateAction(secondState, "SecondUpdateAction", [&](float dt)->void{++callCount; });

	//On first Update component will go to initial state
	component.Update();
	CallMultipleUpdate(5);

	CHECK_EQUAL(5,callCount);
}

