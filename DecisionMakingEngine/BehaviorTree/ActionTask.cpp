#include "ActionTask.h"
#include "BehaviorTreeComponent.h"

using TaskResult = Task::TaskResult;

ActionTask::ActionTask(BehaviorTreeComponent* owner, DME::ActionName actionName)
{
	this->owner = owner;
	SetTaskName(actionName);
}


ActionTask::~ActionTask()
{
	//delete action;
}

TaskResult ActionTask::ProcessTask(float dt)
{
	if (taskName == "")
		return TaskResult::None;

	return owner->GetTask(taskName)->Invoke(dt);
}

void ActionTask::SetTaskName(DME::ActionName name)
{
	this->taskName = name;
}

DME::ActionName ActionTask::GetTaskName() const
{
	return taskName;
}
