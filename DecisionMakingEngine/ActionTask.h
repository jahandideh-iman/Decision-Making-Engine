#pragma once
#include "BehaviorTask.h"
#include <functional>

using std::function;

class ActionTask :
	public BehaviorTask
{
	typedef std::function<bool(float)> Action;
public:
	ActionTask(Action action);
	~ActionTask();

	void ProcessTask(float dt) override;

private:
	Action action = nullptr;
};

