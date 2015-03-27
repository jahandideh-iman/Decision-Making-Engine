#include "DecisionTreeComponent.h"
//TODO: Find out why I can't include this in the header file
#include "DecisionTreeNode.h"

DecisionTreeComponent::DecisionTreeComponent(DecisionTreeNode* root)
{
	SetRoot(root);
}


DecisionTreeComponent::~DecisionTreeComponent()
{
	delete root;
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
	actions[actionName] = nullptr;
}

void DecisionTreeComponent::SetActionMethod(ActionName actionName, UpdateAction action)
{
	actions[actionName] = action;
}

UpdateAction DecisionTreeComponent::GetActionMethod(ActionName actionName)
{
	return actions[actionName];
}

void DecisionTreeComponent::AddCondition(ConditionName conditionName)
{
	conditions[conditionName] = nullptr;
}

void DecisionTreeComponent::SetConditionMethod(ConditionName conditionName, Condition condition)
{
	conditions[conditionName] = condition;
}

Condition DecisionTreeComponent::GetConditionMethod(ConditionName conditionName)
{
	return conditions[conditionName];
}

