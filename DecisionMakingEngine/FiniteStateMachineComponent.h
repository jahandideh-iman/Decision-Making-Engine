#pragma once

#include <map>
#include <string>
#include <vector>
#include "DMEComponent.h"
#include "DMEDefines.h"

using std::map;
using std::string;

typedef string StateName;

using DME::Action;
using DME::Query;

class FiniteStateMachineComponent : public DMEComponent
{
private:
	struct State;

	struct StateTransition
	{
		StateTransition(State* destination, Query query)
		{
			this->destinationState = destination;
			this->query = query;
		}

		State* destinationState;
		Query query;
		
	};

	struct State
	{
		State(StateName name = "", DME::Action entryAction = nullptr, DME::UpdateAction updateAction = nullptr)
		{
			this->name = name;
			this->entryAction = entryAction;
			this->updateAction = updateAction;
		}

		StateName name;
		DME::Action entryAction;
		DME::Action exitAction;
		DME::UpdateAction updateAction;

		std::vector<StateTransition> transitions;
	};

	typedef map<StateName, State> StateContainer;

public:
	FiniteStateMachineComponent();
	~FiniteStateMachineComponent();

	void Update(float dt = 0) override;

	void AddState(StateName stateName);
	void SetInitialState(StateName stateName);

	void SetTransition(StateName from, StateName to, Query condition);

	void SetStateEntryAction(StateName stateName, DME::Action action);
	void SetStateUpdateAction(StateName stateName, DME::UpdateAction action);
	void SetStateExitAction(StateName stateName, DME::Action action);

	StateName GetCurrentStateName();

	bool HasState(StateName stateName);
	bool HasNoState();

private:
	void ProcessCurrentStateTransitions();
	void GoToState(State* newState);

	void CallExitActionFor(State* state);
	void CallEntryActionFor(State* state);
	void CallUpdateActionFor(State* state, float dt);

	bool FiniteStateMachineComponent::IsTheFirstUpdate();


private:

	StateContainer states;
	State* currentState;
	StateName initialStateName;

};

