#include "FiniteStateComponent.h"


FiniteStateComponent::FiniteStateComponent()
{
	currentState = "";
	initialState = "";

	stateEntryAction = nullptr;
	stateAction = nullptr;
}


FiniteStateComponent::~FiniteStateComponent()
{
}

void FiniteStateComponent::AddState(StateName state)
{
	if (initialState == "")
		initialState = state;

	states.emplace(state,state);
}

void FiniteStateComponent::Update()
{
	if (currentState != initialState)
		GoToState(initialState);
	if (stateAction != nullptr)
		stateAction();
}

StateName FiniteStateComponent::GetCurrentState()
{
	return currentState;
}

void FiniteStateComponent::SetStateEntryAction(StateName sate, function<void()> entryAction)
{
	stateEntryAction = entryAction;
}

void FiniteStateComponent::GoToState(StateName state)
{
	currentState = state;
	if (stateEntryAction != nullptr)
		stateEntryAction();
}

void FiniteStateComponent::SetStateAction(StateName theOnlyState, function<void() > action)
{
	stateAction = action;
}

bool FiniteStateComponent::HasState(StateName state)
{
	return states.find(state)!= states.end();
}

bool FiniteStateComponent::HasNoState()
{
	return states.empty();
}
