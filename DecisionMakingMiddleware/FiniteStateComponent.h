#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>

using std::function;
using std::map;
using std::string;
using std::vector;

typedef string StateName;


class FiniteStateComponent
{
private:

	typedef function<void()> StateAction;
	typedef function<bool()> ConditionQuery;
	
	struct State;

	struct StateTransition
	{
		StateTransition(State* destination, ConditionQuery query)
		{
			this->destinationState = destination;
			this->query = query;
		}

		State* destinationState;
		ConditionQuery query;
		
	};

	struct State
	{
		State(StateName name = "", StateAction entryAction = nullptr, StateAction loopingAction = nullptr)
		{
			this->name = name;
			this->entryAction = entryAction;
			this->loopingAction = loopingAction;
		}

		StateName name;
		StateAction entryAction;
		StateAction loopingAction;
		StateAction exitAction;

		std::vector<StateTransition> transitions;
	};

	typedef map<StateName, State> StateContainer;


public:
	FiniteStateComponent();
	~FiniteStateComponent();

	void Update();



	void AddState(StateName stateName);
	void SetInitialState(StateName stateName);

	void SetTransition(StateName from, StateName to, ConditionQuery condition);

	void SetStateEntryAction(StateName stateName, StateAction action);
	void SetStateLoopingAction(StateName stateName, StateAction action);
	void SetStateExitAction(StateName stateName, StateAction action);

	StateName GetCurrentStateName();

	bool HasState(StateName stateName);
	bool HasNoState();

private:
	void ProcessCurrentStateTransitions();
	void GoToState(State* newState);

	void CallExitActionFor(State* state);
	void CallEntryActionFor(State* state);
	void CallLoopingActionFor(State* state);

	bool FiniteStateComponent::IsTheFirstUpdate();


private:

	StateContainer states;
	State* currentState;
	StateName initialStateName;

};

