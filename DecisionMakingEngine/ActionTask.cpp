#include "ActionTask.h"


ActionTask::ActionTask(Action action)
{
	this->action = action;
}


ActionTask::~ActionTask()
{
	//delete action;
}

TaskResult ActionTask::ProcessTask(float dt)
{
	if (action != nullptr)
		return action(dt);
}
