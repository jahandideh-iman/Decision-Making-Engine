#include "BehaviorTreeComponent.h"
#include "Core/DMEUtilities.h"
#include "BehaviorTask.h"

using namespace DME;

BehaviorTreeComponent::BehaviorTreeComponent()
{
}

BehaviorTreeComponent::~BehaviorTreeComponent()
{
	SAFE_DELETE(root);
}

void BehaviorTreeComponent::Update(float dt)
{
	if (root != nullptr)
		root->ProcessTask(dt);
}

void BehaviorTreeComponent::SetRoot(BehaviorTask *task)
{
	root = task;
}

const BehaviorTask* BehaviorTreeComponent::GetRoot() const
{
	return root;
}

bool BehaviorTreeComponent::IsEmpty()
{
	return root == nullptr;
}

void BehaviorTreeComponent::AddEmptyTask(TaskName name)
{
	AddEmptyInterface(name);
}

void BehaviorTreeComponent::SetTask(TaskName name, Task* task)
{
	SetInterface(name, task);
}

const Task* BehaviorTreeComponent::GetTask(TaskName name) const
{
	return dynamic_cast<const Task *> (GetInterface(name));
}

