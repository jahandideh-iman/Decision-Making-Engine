#pragma once


typedef char* StateName;

class FiniteStateComponent
{
public:
	FiniteStateComponent();
	~FiniteStateComponent();

	void AddState(StateName state);
	StateName GetState();

private:
	StateName state;
};

