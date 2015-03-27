#include "FiniteStateMachineComponent.h"


FiniteStateMachineComponent::FiniteStateMachineComponent()
{
	initialStateName = "";
	currentState = nullptr;
}


FiniteStateMachineComponent::~FiniteStateMachineComponent()
{
}

void FiniteStateMachineComponent::AddState(StateName stateName)
{
	states.emplace(stateName,  State(stateName));
}


FiniteStateMachineComponent::State* FiniteStateMachineComponent::GetState(StateName stateName)
{
	return &states[stateName];
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
		GoToState(&states[initialStateName]);
		return;
	}
		
	for (const StateTransition& t : currentState->transitions)
	{
		if (conditions[t.conditionName]() == true)
		{
			GoToState(t.destinationState);
			break;
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
		if (state->exitAction != "")
			actions[state->exitAction]();
	}
}

void FiniteStateMachineComponent::CallEntryActionFor(State* state)
{
	if (state != nullptr)
	{
		if (state->entryAction != "")
			actions[state->entryAction]();
	}
}

void FiniteStateMachineComponent::CallUpdateActionFor(State* state,float dt)
{
	if (state != nullptr)
	{
		if (state->updateAction != "")
			updateActions[state->updateAction](dt);
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
	states[stateName].entryAction = action;
}

void FiniteStateMachineComponent::SetStateUpdateAction(StateName stateName, ActionName action)
{
	states[stateName].updateAction = action;
}

void FiniteStateMachineComponent::SetStateExitAction(StateName stateName, ActionName action)
{
	states[stateName].exitAction = action;
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
	conditions[conditionName] = nullptr;
}

void FiniteStateMachineComponent::AddTransition(StateName from, StateName to, ConditionName conditionName)
{
	states[from].transitions.emplace_back(StateTransition(&states[to], conditionName));
}

void FiniteStateMachineComponent::SetConditionMethod(ConditionName conditionName, DME::Condition condition)
{
	conditions[conditionName] = condition;
}

void FiniteStateMachineComponent::SetUpdateActionMethod(ActionName actionName, DME::UpdateAction action)
{
	updateActions[actionName] = action;
}

void FiniteStateMachineComponent::SetActionMethod(ActionName actionName, DME::Action action)
{
	actions[actionName] = action;
}

void FiniteStateMachineComponent::AddAction(ActionName actionName)
{
	actions[actionName] = nullptr;
}

void FiniteStateMachineComponent::AddUpdateAction(ActionName actionName)
{
	updateActions[actionName] = nullptr;
}







