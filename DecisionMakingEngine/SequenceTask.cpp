#include "SequenceTask.h"


SequenceTask::SequenceTask()
{
}


SequenceTask::~SequenceTask()
{
	for (auto task : tasks)
		delete task;
}

void SequenceTask::ProcessTask(float dt)
{
	for (auto task : tasks)
		task->ProcessTask(dt);
}

void SequenceTask::AddTask(BehaviorTask *task)
{
	tasks.push_back(task);
}
