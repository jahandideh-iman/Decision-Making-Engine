#include "DecisionTreeComponent.h"
#include "DecisionTreeNode.h"
#include "Core/Interfaces/Action.h"
#include "Core/Interfaces/Condition.h"
#include "Core/DMEUtilities.h"

DecisionTreeComponent::DecisionTreeComponent(DecisionTreeNode* root)
{
	SetRoot(root);
}


DecisionTreeComponent::~DecisionTreeComponent()
{
	SAFE_DELETE(root);
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
	AddEmptyInterface(actionName);
}

void DecisionTreeComponent::SetActionMethod(ActionName actionName, Action* action)
{
	SetInterface(actionName, action);
}

const Action* DecisionTreeComponent::GetActionMethod(ActionName actionName) const
{
	return dynamic_cast<const Action *> (GetInterface(actionName));
}

void DecisionTreeComponent::AddCondition(ConditionName conditionName)
{
	AddEmptyInterface(conditionName);
}

void DecisionTreeComponent::SetConditionMethod(ConditionName conditionName, Condition* condition)
{
	SetInterface(conditionName, condition);
}

const Condition* DecisionTreeComponent::GetConditionMethod(ConditionName conditionName) const
{
	return dynamic_cast<const Condition *> (GetInterface(conditionName));
}

