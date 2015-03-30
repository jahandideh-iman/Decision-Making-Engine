#include "FiniteStateMachineComponent.h"


FiniteStateMachineComponent::FiniteStateMachineComponent()
{
	initialStateName = "";
	currentState = nullptr;
}


FiniteStateMachineComponent::~FiniteStateMachineComponent()
{
	DELETE_MAP_CONTAINER(states);
	DELETE_MAP_CONTAINER(actions);
	DELETE_MAP_CONTAINER(conditions);
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
		if (conditions[t.conditionName]->GetResult() == true)
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
			DME::Action* action = actions[state->exitActionName];
			if (dynamic_cast<OneTimeCalledAction*> (action) != nullptr)
			{
				dynamic_cast<OneTimeCalledAction*> (action)->Invoke();
			}
		}
	}
}

void FiniteStateMachineComponent::CallEntryActionFor(State* state)
{
	if (state != nullptr)
	{
		if (state->entryActionName != "")
		{
			DME::Action* action = actions[state->entryActionName];
			if (dynamic_cast<OneTimeCalledAction*> (action) != nullptr)
			{
				dynamic_cast<OneTimeCalledAction*> (action)->Invoke();
			}
		}

	}
}

void FiniteStateMachineComponent::CallUpdateActionFor(State* state,float dt)
{
	if (state != nullptr)
	{
		if (state->updateActionName != "")
		{
			DME::Action* action = actions[state->updateActionName];
			if (dynamic_cast<EveryUpdateCalledAction*> (action) != nullptr)
			{
				dynamic_cast<EveryUpdateCalledAction*> (action)->Invoke(dt);
			}
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
	conditions[conditionName] = nullptr;
}

void FiniteStateMachineComponent::AddTransition(StateName from, StateName to, ConditionName conditionName)
{
	states[from]->transitions.emplace_back(StateTransition(states[to], conditionName));
}

void FiniteStateMachineComponent::SetConditionMethod(ConditionName conditionName, Condition* condition)
{
	conditions[conditionName] = condition;
}

void FiniteStateMachineComponent::SetActionMethod(ActionName actionName, DME::Action* action)
{
	actions[actionName] = action;
}

void FiniteStateMachineComponent::AddAction(ActionName actionName)
{
	actions[actionName] = nullptr;
}


StateName FiniteStateMachineComponent::GetInitialStateName() const
{
	return initialStateName;
}







