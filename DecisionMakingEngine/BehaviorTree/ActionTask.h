#pragma once
#include "BehaviorTask.h"
#include "Core/DMEDefines.h"
#include <functional>

using std::function;

class BehaviorTreeComponent;

class ActionTask :
	public BehaviorTask
{
public:
	ActionTask(BehaviorTreeComponent* owner, DME::TaskName taskName = "");
	~ActionTask();

	Task::TaskResult ProcessTask(float dt) override;

	void SetTaskName(DME::TaskName name);
	DME::ActionName GetTaskName() const;
	
private:
	DME::TaskName taskName;
	BehaviorTreeComponent* owner = nullptr;
};

