#include "CompoundTask.h"


CompoundTask::CompoundTask()
{
}


CompoundTask::~CompoundTask()
{
	for (auto task : tasks)
		delete task;
}

void CompoundTask::AddTask(BehaviorTask * task)
{
	tasks.push_back(task);
}

void CompoundTask::RestartTasksIndex()
{
	currentTaskIndex = 0u;
}

const BehaviorTask * CompoundTask::GetChild(int index)
{
	if (index < tasks.size())
		return tasks[index];

	return nullptr;
}
