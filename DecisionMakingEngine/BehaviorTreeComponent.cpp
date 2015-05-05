#include "BehaviorTreeComponent.h"
#include <cassert>
#include "DMEUtilities.h"

using namespace DME;

BehaviorTreeComponent::BehaviorTreeComponent()
{
}


BehaviorTreeComponent::~BehaviorTreeComponent()
{
	SAFE_DELETE(root);
	DELETE_MAP_CONTAINER(actions);
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

void BehaviorTreeComponent::AddAction(ActionName actionName)
{
	actions.emplace(actionName, nullptr);
}

void BehaviorTreeComponent::SetActionMethod(ActionName actionName, TaskMethod* action)
{
	actions[actionName] = action;
}

const TaskMethod* BehaviorTreeComponent::GetActionMethod(ActionName actionName) const
{
	assert(actions.find(actionName) != actions.end());
	return actions.find(actionName)->second;
}

