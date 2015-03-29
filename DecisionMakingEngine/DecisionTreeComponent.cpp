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

	for (auto action : actions)
		delete action.second;

	for (auto condition : conditions)
		delete condition.second;
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

const EveryUpdateCalledAction* DecisionTreeComponent::GetActionMethod(ActionName actionName)
{
	return actions[actionName];
}

void DecisionTreeComponent::AddCondition(ConditionName conditionName)
{
	conditions[conditionName] = nullptr;
}

void DecisionTreeComponent::SetConditionMethod(ConditionName conditionName, Condition* condition)
{
	conditions[conditionName] = condition;
}

const Condition* DecisionTreeComponent::GetConditionMethod(ConditionName conditionName)
{
	return conditions[conditionName];
}

