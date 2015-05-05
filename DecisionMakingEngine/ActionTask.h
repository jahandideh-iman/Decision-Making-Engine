#pragma once
#include "BehaviorTask.h"
#include "DMEDefines.h"
#include <functional>

using std::function;

class BehaviorTreeComponent;

class ActionTask :
	public BehaviorTask
{
	typedef std::function<TaskResult(float)> Action;
public:
	ActionTask(BehaviorTreeComponent* owner, DME::ActionName actioName = "");
	~ActionTask();

	TaskResult ProcessTask(float dt) override;
	
private:
	DME::ActionName actionName;
	BehaviorTreeComponent* owner = nullptr;
};

