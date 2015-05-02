#pragma once
#include "BehaviorTask.h"
#include <functional>

using std::function;

class ActionTask :
	public BehaviorTask
{
	typedef std::function<TaskResult(float)> Action;
public:
	ActionTask(Action action);
	~ActionTask();

	TaskResult ProcessTask(float dt) override;

private:
	Action action = nullptr;
};

