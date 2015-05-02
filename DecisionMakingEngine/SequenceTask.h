#pragma once
#include "BehaviorTask.h"
#include <vector>

class SequenceTask :
	public BehaviorTask
{
public:
	SequenceTask();
	~SequenceTask();

	TaskResult ProcessTask(float dt) override;
	void AddTask(BehaviorTask *task);

private:
	std::vector<BehaviorTask *> tasks;

	unsigned currentTaskIndex = 0u;
};

