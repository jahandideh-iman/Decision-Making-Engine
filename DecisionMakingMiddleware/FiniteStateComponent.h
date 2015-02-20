#pragma once

#include <functional>

using std::function;


typedef char* StateName;

class FiniteStateComponent
{
public:
	FiniteStateComponent();
	~FiniteStateComponent();

	void AddState(StateName state);
	StateName GetState();
	void Update();

	void ChangeState();

	StateName GetCurrentState();
	void SetStateEntryAction(StateName theOnlyState, function<void()> action);
	void SetStateAction(StateName theOnlyState, function<void() > action);
private:
	StateName state;
	StateName currentState;

	function<void()> stateEntryAction;
	function<void()> stateAction;

};

