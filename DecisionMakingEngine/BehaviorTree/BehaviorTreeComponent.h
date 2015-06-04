#pragma once
#include "Core/DMEComponent.h"
#include "Core/DMEDefines.h"
#include "BehaviorTree/Task.h"

class BehaviorTask;

class BehaviorTreeComponent :
	public DMEComponent
{
public:
	BehaviorTreeComponent();
	~BehaviorTreeComponent();

	void Update(float dt = 0) override;

	void SetRoot(BehaviorTask *task);
	const BehaviorTask* GetRoot() const;
	bool IsEmpty();

	void AddEmptyTask(DME::TaskName name);
	void SetTask(DME::TaskName name, Task* task);
	const Task* GetTask(DME::TaskName name) const;
private:
	BehaviorTask *root = nullptr;

};
