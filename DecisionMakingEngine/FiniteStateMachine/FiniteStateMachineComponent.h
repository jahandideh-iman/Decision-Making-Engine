#pragma once

#include <map>
#include <string>
#include <vector>
#include "Core/DMEComponent.h"
#include "Core/DMEDefines.h"


namespace DME
{
	class Action;
	class Condition;
}


class FiniteStateMachineComponent : public DMEComponent
{
	using ConditionName = DME::ConditionName;
	using ActionName = DME::ActionName;
	using Action = DME::Action;
	using ConditionName = DME::ConditionName;
	using Condition = DME::Condition;

	using StateName = DME::StateName;

	struct State;

public:
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
			this->entryActionName = entryAction;
			this->updateActionName = updateAction;
			this->exitActionName = exitAction;
		}

		StateName name;
		ActionName entryActionName;
		ActionName exitActionName;
		ActionName updateActionName;

		std::vector<StateTransition> transitions;
	};

	typedef std::map<StateName, State*> StateContainer;

public:
	FiniteStateMachineComponent();
	~FiniteStateMachineComponent();

	void Update(float dt = 0) override;

	void AddState(StateName stateName);
	void SetInitialState(StateName stateName);
	StateName GetCurrentStateName();
	StateName GetInitialStateName() const;
	const State* GetState(StateName stateName) const;


	void AddCondition(ConditionName conditionName);
	void SetConditionMethod(ConditionName conditionName, Condition* condition);

	void AddAction(ActionName actionName);
	void SetActionMethod(ActionName actionName, DME::Action* action);

	void SetStateEntryAction(StateName stateName, ActionName action);
	void SetStateUpdateAction(StateName stateName, ActionName action);
	void SetStateExitAction(StateName stateName, ActionName action);

	void AddTransition(StateName from, StateName to, ConditionName conditionName);

	bool HasState(StateName stateName);
	bool HasNoState();

private:
	void ProcessCurrentStateTransitions();
	void GoToState(State* newState);

	void CallExitActionFor(State* state);
	void CallEntryActionFor(State* state);
	void CallUpdateActionFor(State* state, float dt);

	const Action *GetAction(ActionName name);
	const Condition *GetCondition(ConditionName name);

	bool IsTheFirstUpdate();

private:

	StateContainer states;

	State* currentState;
	StateName initialStateName;

};

