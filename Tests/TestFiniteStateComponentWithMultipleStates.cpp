#include "CppUTest/TestHarness.h"
#include "FiniteStateComponent.h"

TEST_GROUP(FiniteStateComponentWithMultipleStates)
{
	FiniteStateComponent component;
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

TEST(FiniteStateComponentWithMultipleStates, StateIsNotChangedAfterFirstUpdate)
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
	component.SetStateEntryAction(secondState, [&]()->void{isExecuted = true; });

	//On first Update component will go to initial state
	component.Update();
	component.Update();

	CHECK_TRUE(isExecuted);
}

TEST(FiniteStateComponentWithMultipleStates, ExistActionForSourceIsCalledOnStateTransition)
{
	bool isExecuted = false;

	component.SetTransition(firstState, secondState, []()->bool{return true; });
	component.SetStateExitAction(firstState, [&]()->void{isExecuted = true; });

	//On first Update component will go to initial state
	component.Update();
	component.Update();

	CHECK_TRUE(isExecuted);
}

TEST(FiniteStateComponentWithMultipleStates, LoopingActionIsCallOnEachUpdateAfterTransition)
{
	auto callCount = 0u;

	component.SetTransition(firstState, secondState, []()->bool{return true; });
	component.SetStateLoopingAction(secondState, [&]()->void{++callCount; });

	//On first Update component will go to initial state
	component.Update();
	CallMultipleUpdate(5);

	CHECK_EQUAL(5,callCount);
}

