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
		if (t.query() == true)
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
		if (state->exitAction != nullptr)
			state->exitAction();
	}
}

void FiniteStateMachineComponent::CallEntryActionFor(State* state)
{
	if (state != nullptr)
	{
		if (state->entryAction != nullptr)
			state->entryAction();
	}
}

void FiniteStateMachineComponent::CallUpdateActionFor(State* state,float dt)
{
	if (state != nullptr)
	{
		if (state->updateAction != nullptr)
			state->updateAction(dt);
	}
}

StateName FiniteStateMachineComponent::GetCurrentStateName()
{
	if (currentState == nullptr)
		return "";
	return currentState->name;
}

void FiniteStateMachineComponent::SetStateEntryAction(StateName stateName, DME::Action action)
{
	states[stateName].entryAction = action;
}

void FiniteStateMachineComponent::SetStateUpdateAction(StateName stateName, DME::UpdateAction action)
{
	states[stateName].updateAction = action;
}

void FiniteStateMachineComponent::SetStateExitAction(StateName stateName, DME::Action action)
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

void FiniteStateMachineComponent::SetTransition(StateName from, StateName to, Query query)
{
	states[from].transitions.emplace_back(StateTransition(&states[to], query));
}






