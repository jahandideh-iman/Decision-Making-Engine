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

	void SetStateEntryAction(StateName stateName, ActionName actionName, DME::OneTimeCalledAction* action)
	{
		component.AddAction(actionName);
		component.SetActionMethod(actionName, action);
		component.SetStateEntryAction(stateName, actionName);
	}

	void SetStateUpdateAction(StateName stateName, ActionName actionName, DME::EveryUpdateCalledAction* action)
	{
		component.AddAction(actionName);
		component.SetActionMethod(actionName, action);
		component.SetStateUpdateAction(stateName, actionName);
	}

	void SetStateExitAction(StateName stateName, ActionName actionName, DME::OneTimeCalledAction* action)
	{
		component.AddAction(actionName);
		component.SetActionMethod(actionName, action);
		component.SetStateExitAction(stateName, actionName);
	}

	void SetTransition(StateName from, StateName to,ConditionName conditionName ,Condition* condition)
	{
		component.AddCondition(conditionName);
		component.SetConditionMethod(conditionName, condition);
		component.AddTransition(from, to, conditionName);
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
	SetTransition(firstState, secondState, "ConditionOne" ,new Condition([]()->bool{return false; }));

	//On first Update component will go to initial state
	component.Update();
	component.Update();

	CheckCurrentStateNameIs(firstState);
}


TEST(FiniteStateComponentWithMultipleStates, StateIsChangedWhenTransitionConditionIsMet)
{
	SetTransition(firstState, secondState,"ConditionOne" ,new Condition([]()->bool{return true; }));

	//On first Update component will go to initial state
	component.Update();
	component.Update();

	CheckCurrentStateNameIs(secondState);
}

TEST(FiniteStateComponentWithMultipleStates, StateIsSetToInitialStateOnFirstUpdate)
{
	SetTransition(firstState, secondState, "ConditionOne", new Condition([]()->bool{return true; }));

	//On first Update component will go to initial state
	component.Update();
	CheckCurrentStateNameIs(firstState);
}

TEST(FiniteStateComponentWithMultipleStates, StateIsNotChangedAfterTransition)
{
	SetTransition(firstState, secondState, "ConditionOne", new Condition([]()->bool{return true; }));

	//On first Update component will go to initial state
	component.Update();
	CallMultipleUpdate(5);

	CheckCurrentStateNameIs(secondState);
}

TEST(FiniteStateComponentWithMultipleStates, EntryActionForDestinationIsCalledOnStateTransition)
{
	bool isExecuted = false;

	SetTransition(firstState, secondState, "ConditionOne", new Condition([]()->bool{return true; }));
	SetStateEntryAction(secondState, "SecondEntryAction" , new OneTimeCalledAction([&]()->void{isExecuted = true; }));

	//On first Update component will go to initial state
	component.Update();
	component.Update();

	CHECK_TRUE(isExecuted);
}

TEST(FiniteStateComponentWithMultipleStates, ExistActionForSourceIsCalledOnStateTransition)
{
	bool isExecuted = false;

	SetTransition(firstState, secondState, "ConditionOne", new Condition([]()->bool{return true; }));
	SetStateExitAction(firstState, "FirstExitAction" ,new OneTimeCalledAction([&]()->void{isExecuted = true; }));

	//On first Update component will go to initial state
	component.Update();
	component.Update();

	CHECK_TRUE(isExecuted);
}

TEST(FiniteStateComponentWithMultipleStates, UpdateActionIsCallOnEachUpdateAfterTransition)
{
	auto callCount = 0u;

	SetTransition(firstState, secondState, "ConditionOne", new Condition([]()->bool{return true; }));
	SetStateUpdateAction(secondState, "SecondUpdateAction", new EveryUpdateCalledAction([&](float dt)->void{++callCount; }));

	//On first Update component will go to initial state
	component.Update();
	CallMultipleUpdate(5);

	CHECK_EQUAL(5,callCount);
}

