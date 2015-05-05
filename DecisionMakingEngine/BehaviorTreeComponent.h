#pragma once
#include "DMEComponent.h"
#include "BehaviorTask.h"
#include "DMEDefines.h"
#include "TaskMethod.h"
#include <map>


class BehaviorTreeComponent :
	public DMEComponent
{
	typedef std::map<DME::ActionName, TaskMethod*> ActionContainer;
public:
	BehaviorTreeComponent();
	~BehaviorTreeComponent();

	void Update(float dt = 0) override;

	void SetRoot(BehaviorTask *task);
	bool IsEmpty();

	void AddAction(DME::ActionName actionName);
	void SetActionMethod(DME::ActionName actionName, TaskMethod* action);
	const TaskMethod* GetActionMethod(DME::ActionName actionName) const;
private:
	BehaviorTask *root = nullptr;

	ActionContainer actions;
};

