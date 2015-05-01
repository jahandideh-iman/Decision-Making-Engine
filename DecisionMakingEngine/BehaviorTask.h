#pragma once
class BehaviorTask
{
public:
	BehaviorTask();
	virtual ~BehaviorTask();

	virtual void ProcessTask(float dt) = 0;
};

