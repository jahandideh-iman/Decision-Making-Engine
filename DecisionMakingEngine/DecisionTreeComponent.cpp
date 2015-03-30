#include "DecisionTreeComponent.h"
//TODO: Find out why I can't include this in the header file
#include "DecisionTreeNode.h"
#include <assert.h>

DecisionTreeComponent::DecisionTreeComponent(DecisionTreeNode* root)
{
	SetRoot(root);
}


DecisionTreeComponent::~DecisionTreeComponent()
{
	SAFE_DELETE(root);
	DELETE_MAP_CONTAINER(actions);
	DELETE_MAP_CONTAINER(conditions);
}

bool DecisionTreeComponent::IsEmpty() const
{
	return root == nullptr;
}

void DecisionTreeComponent::SetRoot(DecisionTreeNode* root)
{
	this->root = root;
}

const DecisionTreeNode* DecisionTreeComponent::GetRoot() const
{
	return root;
}

void DecisionTreeComponent::Update(float dt)
{
	root->ProcessNode(dt);
}

void DecisionTreeComponent::AddAction(ActionName actionName)
{
	actions.emplace(actionName, nullptr);
}

void DecisionTreeComponent::SetActionMethod(ActionName actionName, EveryUpdateCalledAction* action)
{
	actions[actionName] = action;
}

const EveryUpdateCalledAction* DecisionTreeComponent::GetActionMethod(ActionName actionName) const
{
	assert(actions.find(actionName) != actions.end());
	return actions.find(actionName)->second;
}

void DecisionTreeComponent::AddCondition(ConditionName conditionName)
{
	conditions[conditionName] = nullptr;
}

void DecisionTreeComponent::SetConditionMethod(ConditionName conditionName, Condition* condition)
{
	conditions[conditionName] = condition;
}

const Condition* DecisionTreeComponent::GetConditionMethod(ConditionName conditionName) const
{
	assert(conditions.find(conditionName) != conditions.end());
	return conditions.find(conditionName)->second;
}

