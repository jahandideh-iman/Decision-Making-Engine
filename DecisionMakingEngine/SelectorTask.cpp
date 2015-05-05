#include "SelectorTask.h"


SelectorTask::SelectorTask()
{
}

TaskResult SelectorTask::ProcessTask(float dt)
{
	for (; currentTaskIndex < tasks.size(); ++currentTaskIndex)
	{
		auto taskResult = tasks[currentTaskIndex]->ProcessTask(dt);

		if (taskResult != TaskResult::Failure)
		{
			if (taskResult == TaskResult::Success)
				RestartTasksIndex();
			return taskResult;
		}
	}
	RestartTasksIndex();
	return TaskResult::Failure;
}
