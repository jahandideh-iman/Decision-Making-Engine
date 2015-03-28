#include "DecisionNode.h"


DecisionNode::DecisionNode(DecisionTreeComponent* owner, ConditionName conditionName, DecisionTreeNode* truePathNode, DecisionTreeNode* falsePathNode)
: DecisionTreeNode(owner)
{
	SetConditionName(conditionName);
	SetTruePathNode(truePathNode);
	SetFalsePathNode(falsePathNode);
}


DecisionNode::~DecisionNode()
{
	SAFE_DELETE(truePathNode);
	SAFE_DELETE(falsePathNode);
}

void DecisionNode::ProcessNode(float dt)
{
	if (owner->GetConditionMethod(conditionName)())
		truePathNode->ProcessNode(dt);
	else
		falsePathNode->ProcessNode(dt);
}

void DecisionNode::SetConditionName(ConditionName conditionName)
{
	this->conditionName = conditionName;
}

void DecisionNode::SetTruePathNode(DecisionTreeNode* node)
{
	truePathNode = node;
}

void DecisionNode::SetFalsePathNode(DecisionTreeNode* node)
{
	falsePathNode = node;
}

ConditionName DecisionNode::GetConditionName() const
{
	return conditionName;
}

const DecisionTreeNode* DecisionNode::GetTruePathNode() const
{
	return truePathNode;
}

const DecisionTreeNode* DecisionNode::GetFalsePathNode() const
{
	return falsePathNode;
}
