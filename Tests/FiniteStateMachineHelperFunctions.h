#pragma once

#include "FiniteStateMachineComponent.h";
#include "CppUTest/TestHarness.h"


static void SetTransition(FiniteStateMachineComponent* comp, StateName from, StateName to, ConditionName conditionName, Condition* condition)
{
	comp->AddCondition(conditionName);
	comp->SetConditionMethod(conditionName, condition);
	comp->AddTransition(from, to, conditionName);
}

static void CallMultipleUpdate(FiniteStateMachineComponent* comp, unsigned numberOfTimes)
{
	for (unsigned i = 0; i < numberOfTimes; ++i)
		comp->Update();
}

static void SetStateEntryAction(FiniteStateMachineComponent* comp, StateName stateName, ActionName actionName, DME::OneTimeCalledAction* action)
{
	comp->AddAction(actionName);
	comp->SetActionMethod(actionName, action);
	comp->SetStateEntryAction(stateName, actionName);
}

static void SetStateUpdateAction(FiniteStateMachineComponent* comp, StateName stateName, ActionName actionName, DME::EveryUpdateCalledAction* action)
{
	comp->AddAction(actionName);
	comp->SetActionMethod(actionName, action);
	comp->SetStateUpdateAction(stateName, actionName);
}

static void SetStateExitAction(FiniteStateMachineComponent* comp, StateName stateName, ActionName actionName, DME::OneTimeCalledAction* action)
{
	comp->AddAction(actionName);
	comp->SetActionMethod(actionName, action);
	comp->SetStateExitAction(stateName, actionName);
}


static void CheckCurrentStateNameIs(FiniteStateMachineComponent* comp, StateName stateName)
{
	CHECK_EQUAL(stateName, comp->GetCurrentStateName());
}