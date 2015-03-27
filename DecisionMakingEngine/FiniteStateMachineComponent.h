#pragma once

#include <map>
#include <string>
#include <vector>
#include "DMEComponent.h"
#include "DMEDefines.h"

using std::map;
using std::string;
using DME::Action;
using DME::Condition;

using DME::ActionName;
using DME::ConditionName;
using DME::StateName;

class FiniteStateMachineComponent : public DMEComponent
{
public:

	struct State;

	struct StateTransition
	{
		StateTransition(State* destination, ConditionName condition)
		{
			this->destinationState = destination;
			this->conditionName = condition;
		}

		State* destinationState;
		ConditionName conditionName;
		
	};

	struct State
	{
		State(StateName name = "", ActionName entryAction = "", ActionName updateAction = "", ActionName exitAction = "")
		{
			this->name = name;
			this->entryAction = entryAction;
			this->updateAction = updateAction;
			this->exitAction = exitAction;
		}

		StateName name;
		ActionName entryAction;
		ActionName exitAction;
		ActionName updateAction;

		std::vector<StateTransition> transitions;
	};


	typedef map<StateName, State> StateContainer;
	typedef map<ActionName, DME::Action> ActionContainer;
	typedef map<ActionName, DME::UpdateAction> UpdateActionContainer;
	typedef map<ConditionName, Condition> ConditionContainer;

public:
	FiniteStateMachineComponent();
	~FiniteStateMachineComponent();

	void Update(float dt = 0) override;

	void AddState(StateName stateName);
	void SetInitialState(StateName stateName);

	void AddCondition(ConditionName conditionName);
	void AddTransition(StateName from, StateName to, ConditionName conditionName);
	void SetConditionMethod(ConditionName conditionName, DME::Condition condition);

	void AddAction(ActionName actionName);
	void AddUpdateAction(ActionName actionName);

	void SetUpdateActionMethod(ActionName actionName, DME::UpdateAction action);
	void SetActionMethod(ActionName actionName, DME::Action action);

	void SetStateEntryAction(StateName stateName, ActionName action);
	void SetStateUpdateAction(StateName stateName, ActionName action);
	void SetStateExitAction(StateName stateName, ActionName action);

	StateName GetCurrentStateName();

	bool HasState(StateName stateName);
	bool HasNoState();

	State* GetState(StateName stateName);

private:
	void ProcessCurrentStateTransitions();
	void GoToState(State* newState);

	void CallExitActionFor(State* state);
	void CallEntryActionFor(State* state);
	void CallUpdateActionFor(State* state, float dt);

	bool FiniteStateMachineComponent::IsTheFirstUpdate();


private:

	StateContainer states;
	ConditionContainer conditions;
	//TODO: find a  way to merge these two 
	ActionContainer actions;
	UpdateActionContainer updateActions;

	State* currentState;
	StateName initialStateName;

};

