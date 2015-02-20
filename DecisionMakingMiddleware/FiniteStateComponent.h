#pragma once

#include <functional>
#include <map>
#include <string>

using std::function;
using std::map;
using std::string;



typedef string StateName;

typedef map<StateName, StateName> StateContainer;

class FiniteStateComponent
{
public:
	FiniteStateComponent();
	~FiniteStateComponent();

	void Update();
	void AddState(StateName state);
	void SetStateEntryAction(StateName theOnlyState, function<void()> action);
	void SetStateAction(StateName theOnlyState, function<void() > action);

	StateName GetCurrentState();

	bool HasState(StateName state);
	bool HasNoState();

private:
	void GoToState(StateName state);

private:

	StateContainer states;
	StateName currentState;
	StateName initialState;

	function<void()> stateEntryAction;
	function<void()> stateAction;

};

