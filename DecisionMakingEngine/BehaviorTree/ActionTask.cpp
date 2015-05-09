#include "ActionTask.h"
#include "BehaviorTreeComponent.h"


ActionTask::ActionTask(BehaviorTreeComponent* owner, DME::ActionName actionName)
{
	this->owner = owner;
	this->actionName = actionName;
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
