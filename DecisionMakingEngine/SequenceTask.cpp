#include "SequenceTask.h"

SequenceTask::SequenceTask()
{
}

TaskResult SequenceTask::ProcessTask(float dt)
{
	for (; currentTaskIndex < tasks.size(); ++currentTaskIndex)
	{
		auto taskResult = tasks[currentTaskIndex]->ProcessTask(dt);

		if (taskResult != TaskResult::Success)
		{
			if (taskResult == TaskResult::Failure)
				RestartTasksIndex();
			return taskResult;
		}
	}
	RestartTasksIndex();
	return TaskResult::Success;
}
