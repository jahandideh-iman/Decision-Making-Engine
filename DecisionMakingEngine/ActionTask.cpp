#include "ActionTask.h"


ActionTask::ActionTask(Action action)
{
	this->action = action;
}


ActionTask::~ActionTask()
{
	//delete action;
}

void ActionTask::ProcessTask(float dt)
{
	if (action != nullptr)
		action(dt);
}
