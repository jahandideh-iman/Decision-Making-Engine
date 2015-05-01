#include "BehaviorTreeComponent.h"


BehaviorTreeComponent::BehaviorTreeComponent()
{
}


BehaviorTreeComponent::~BehaviorTreeComponent()
{
	delete root;
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

bool BehaviorTreeComponent::IsEmpty()
{
	return root == nullptr;
}
