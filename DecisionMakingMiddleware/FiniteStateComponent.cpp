#include "FiniteStateComponent.h"


FiniteStateComponent::FiniteStateComponent()
{
	initialStateName = "";
	currentState = nullptr;
}


FiniteStateComponent::~FiniteStateComponent()
{
}

void FiniteStateComponent::AddState(StateName stateName)
{
	states.emplace(stateName,  State(stateName));
}

void FiniteStateComponent::Update(float dt)
{
	ProcessCurrentStateTransitions();
	CallLoopingActionFor(currentState);
}

bool FiniteStateComponent::IsTheFirstUpdate()
{
	return currentState == nullptr;
}
void FiniteStateComponent::ProcessCurrentStateTransitions()
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

void FiniteStateComponent::GoToState(State* newState)
{
	CallExitActionFor(currentState);

	currentState = newState;
	
	CallEntryActionFor(newState);
}

void FiniteStateComponent::CallExitActionFor(State* state)
{
	if (state != nullptr)
	{
		if (state->exitAction != nullptr)
			state->exitAction();
	}
}

void FiniteStateComponent::CallEntryActionFor(State* state)
{
	if (state != nullptr)
	{
		if (state->entryAction != nullptr)
			state->entryAction();
	}
}

void FiniteStateComponent::CallLoopingActionFor(State* state)
{
	if (state != nullptr)
	{
		if (state->loopingAction != nullptr)
			state->loopingAction();
	}
}

StateName FiniteStateComponent::GetCurrentStateName()
{
	if (currentState == nullptr)
		return "";
	return currentState->name;
}

void FiniteStateComponent::SetStateEntryAction(StateName stateName, StateAction action)
{
	states[stateName].entryAction = action;
}

void FiniteStateComponent::SetStateLoopingAction(StateName stateName, StateAction action)
{
	states[stateName].loopingAction = action;
}

void FiniteStateComponent::SetStateExitAction(StateName stateName, StateAction action)
{
	states[stateName].exitAction = action;
}

bool FiniteStateComponent::HasState(StateName stateName)
{
	return states.find(stateName) != states.end();
}

bool FiniteStateComponent::HasNoState()
{
	return states.empty();
}


//TODO: Find a way to make it only be set on creation
void FiniteStateComponent::SetInitialState(StateName stateName)
{
	initialStateName = stateName;
}

void FiniteStateComponent::SetTransition(StateName from, StateName to, ConditionQuery query)
{
	states[from].transitions.emplace_back(StateTransition(&states[to], query));
}






