#include "SequenceTask.h"


SequenceTask::SequenceTask()
{
}


SequenceTask::~SequenceTask()
{
	for (auto task : tasks)
		delete task;
}

TaskResult SequenceTask::ProcessTask(float dt)
{
	for (; currentTaskIndex < tasks.size(); ++currentTaskIndex)
	{
		auto taskResult = tasks[currentTaskIndex]->ProcessTask(dt);

		if (taskResult != TaskResult::Success)
		{
			if (taskResult == TaskResult::Failure)
				currentTaskIndex = 0; // restart tasks
			return taskResult;
		}
	}
	currentTaskIndex = 0;
	return TaskResult::Success;
}

void SequenceTask::AddTask(BehaviorTask *task)
{
	tasks.push_back(task);
}
