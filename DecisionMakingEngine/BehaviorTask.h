#pragma once

enum TaskResult
{
	None, Unfinished, Success, Failure,
};

class BehaviorTask
{

public:
	BehaviorTask();
	virtual ~BehaviorTask();

	virtual TaskResult ProcessTask(float dt) = 0;
};

