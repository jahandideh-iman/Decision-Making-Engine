#pragma once

#include "CppUTest/TestHarness.h"
#include "FiniteStateMachineComponent.h"

TEST_BASE(FiniteStateComponentTestBase)
{
public:
	FiniteStateMachineComponent* component = nullptr;

	void setup()
	{
		component = new FiniteStateMachineComponent();
	}

	void teardown()
	{
		delete component;
	}

	void SetTransition(StateName from, StateName to, ConditionName conditionName, Condition* condition)
	{
		component->AddCondition(conditionName);
		component->SetConditionMethod(conditionName, condition);
		component->AddTransition(from, to, conditionName);
	}

	void CallMultipleUpdate( unsigned numberOfTimes)
	{
		for (unsigned i = 0; i < numberOfTimes; ++i)
			component->Update();
	}

	void SetStateEntryAction(StateName stateName, ActionName actionName, DME::OneTimeCalledAction* action)
	{
		component->AddAction(actionName);
		component->SetActionMethod(actionName, action);
		component->SetStateEntryAction(stateName, actionName);
	}

	void SetStateUpdateAction(StateName stateName, ActionName actionName, DME::EveryUpdateCalledAction* action)
	{
		component->AddAction(actionName);
		component->SetActionMethod(actionName, action);
		component->SetStateUpdateAction(stateName, actionName);
	}

	void SetStateExitAction(StateName stateName, ActionName actionName, DME::OneTimeCalledAction* action)
	{
		component->AddAction(actionName);
		component->SetActionMethod(actionName, action);
		component->SetStateExitAction(stateName, actionName);
	}


	void CheckCurrentStateNameIs(StateName stateName)
	{
		CHECK_EQUAL(stateName, component->GetCurrentStateName());
	}
};