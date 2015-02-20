#include "FiniteStateComponent.h"


FiniteStateComponent::FiniteStateComponent()
{
	state = "";
	currentState = "";

	stateEntryAction = nullptr;
	stateAction = nullptr;
}


FiniteStateComponent::~FiniteStateComponent()
{
}

void FiniteStateComponent::AddState(StateName state)
{
	this->state = state;
}

StateName FiniteStateComponent::GetState()
{
	return state;
}

void FiniteStateComponent::Update()
{
	if (currentState != state)
		ChangeState();
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

void FiniteStateComponent::ChangeState()
{
	currentState = state;
	if (stateEntryAction != nullptr)
		stateEntryAction();
}

void FiniteStateComponent::SetStateAction(StateName theOnlyState, function<void() > action)
{
	stateAction = action;
}
