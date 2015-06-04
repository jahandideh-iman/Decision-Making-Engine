#include "FiniteStateMachineComponent.h"

#include "Core/Interfaces/Condition.h"
#include "Core/Interfaces/Action.h"
#include "Core/DMEUtilities.h"

using std::map;
using std::string;

using DME::Condition;
using DME::Action;
using DME::ActionName;
using DME::ConditionName;
using DME::StateName;


FiniteStateMachineComponent::FiniteStateMachineComponent()
{
	initialStateName = "";
	currentState = nullptr;
}

FiniteStateMachineComponent::~FiniteStateMachineComponent()
{
	DELETE_MAP_CONTAINER(states);
}

void FiniteStateMachineComponent::AddState(StateName stateName)
{
	states.emplace(stateName,  new State(stateName));
}

const FiniteStateMachineComponent::State* FiniteStateMachineComponent::GetState(StateName stateName) const
{
	return states.find(stateName)->second;
}

void FiniteStateMachineComponent::Update(float dt)
{
	ProcessCurrentStateTransitions();
	CallUpdateActionFor(currentState,dt);
}

bool FiniteStateMachineComponent::IsTheFirstUpdate()
{
	return currentState == nullptr;
}

void FiniteStateMachineComponent::ProcessCurrentStateTransitions()
{
	if (IsTheFirstUpdate())
	{
		GoToState(states[initialStateName]);
		return;
	}
		
	for (const StateTransition& t : currentState->transitions)
	{
		if (GetCondition(t.conditionName)->GetResult() == true)
		{
			GoToState(t.destinationState);
			return;
		}
	}

}

void FiniteStateMachineComponent::GoToState(State* newState)
{
	CallExitActionFor(currentState);

	currentState = newState;
	
	CallEntryActionFor(newState);
}

void FiniteStateMachineComponent::CallExitActionFor(State* state)
{
	if (state != nullptr)
	{
		if (state->exitActionName != "")
		{
			auto action = GetAction(state->exitActionName);
			//TODO: Check for nullptr
			action->Invoke(0);
		}
	}
}

void FiniteStateMachineComponent::CallEntryActionFor(State* state)
{
	if (state != nullptr)
	{
		if (state->entryActionName != "")
		{
			auto action = GetAction(state->entryActionName);
			//TODO: Check for nullptr
			action->Invoke(0);
		}
	}
}

void FiniteStateMachineComponent::CallUpdateActionFor(State* state,float dt)
{
	if (state != nullptr)
	{
		if (state->updateActionName != "")
		{
			auto action = GetAction(state->updateActionName);
			//TODO: Check for nullptr
			action->Invoke(dt);
		}
	}
}

StateName FiniteStateMachineComponent::GetCurrentStateName()
{
	if (currentState == nullptr)
		return "";
	return currentState->name;
}

void FiniteStateMachineComponent::SetStateEntryAction(StateName stateName, ActionName action)
{
	states[stateName]->entryActionName = action;
}

void FiniteStateMachineComponent::SetStateUpdateAction(StateName stateName, ActionName action)
{
	states[stateName]->updateActionName = action;
}

void FiniteStateMachineComponent::SetStateExitAction(StateName stateName, ActionName action)
{
	states[stateName]->exitActionName = action;
}

bool FiniteStateMachineComponent::HasState(StateName stateName)
{
	return states.find(stateName) != states.end();
}

bool FiniteStateMachineComponent::HasNoState()
{
	return states.empty();
}


//TODO: Find a way to make it only be set on creation
void FiniteStateMachineComponent::SetInitialState(StateName stateName)
{
	initialStateName = stateName;
}

void FiniteStateMachineComponent::AddCondition(ConditionName conditionName)
{
	AddEmptyInterface(conditionName);
}

void FiniteStateMachineComponent::AddTransition(StateName from, StateName to, ConditionName conditionName)
{
	states[from]->transitions.emplace_back(StateTransition(states[to], conditionName));
}

void FiniteStateMachineComponent::SetConditionMethod(ConditionName conditionName, Condition* condition)
{
	SetInterface(conditionName, condition);
}

void FiniteStateMachineComponent::SetActionMethod(ActionName actionName, DME::Action* action)
{
	SetInterface(actionName, action);
}

void FiniteStateMachineComponent::AddAction(ActionName actionName)
{
	AddEmptyInterface(actionName);
}


StateName FiniteStateMachineComponent::GetInitialStateName() const
{
	return initialStateName;
}

const Action * FiniteStateMachineComponent::GetAction(ActionName name)
{
	return dynamic_cast<const Action *> (GetInterface(name));
}

const Condition * FiniteStateMachineComponent::GetCondition(ConditionName name)
{
	return dynamic_cast<const Condition *> (GetInterface(name));
}
