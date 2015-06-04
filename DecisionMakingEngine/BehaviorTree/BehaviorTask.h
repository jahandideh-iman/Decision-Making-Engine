#pragma once

#include "Task.h"

using TaskResult = Task::TaskResult;

class BehaviorTask 
{

public:
	BehaviorTask();
	virtual ~BehaviorTask();

	virtual TaskResult ProcessTask(float dt) = 0;
};

