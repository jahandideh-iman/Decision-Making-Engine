#include "ActionTask.h"
#include "BehaviorTreeComponent.h"


ActionTask::ActionTask(BehaviorTreeComponent* owner, DME::ActionName actionName)
{
	this->owner = owner;
	SetActionName(actionName);
}


ActionTask::~ActionTask()
{
	//delete action;
}

TaskResult ActionTask::ProcessTask(float dt)
{
	if (actionName == "")
		return TaskResult::None;

	return owner->GetActionMethod(actionName)->Invoke(dt);
}

void ActionTask::SetActionName(DME::ActionName name)
{
	this->actionName = name;
}

DME::ActionName ActionTask::GetActionName() const
{
	return actionName;
}
