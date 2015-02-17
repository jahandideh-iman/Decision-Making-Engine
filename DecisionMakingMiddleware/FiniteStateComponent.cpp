#include "FiniteStateComponent.h"


FiniteStateComponent::FiniteStateComponent()
{
	state = "";
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
