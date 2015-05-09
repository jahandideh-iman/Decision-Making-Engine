#pragma once
#include "BehaviorTask.h"
#include <vector>
class CompoundTask :
	public BehaviorTask
{
public:
	CompoundTask();
	virtual ~CompoundTask();

	void AddTask(BehaviorTask * task);

	//Note: This function is only for testing
	const BehaviorTask * GetChild(int index);
	
protected:
	void RestartTasksIndex();

protected:
	std::vector<BehaviorTask *> tasks;

	unsigned currentTaskIndex = 0u;
};

