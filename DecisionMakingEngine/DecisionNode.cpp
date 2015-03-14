#include "DecisionNode.h"


DecisionNode::DecisionNode(DME::Query query, DecisionTreeNode* truePathNode, DecisionTreeNode* falsePathNode)
{
	SetQuery(query);
	SetTruePathNode(truePathNode);
	SetFalsePathNode(falsePathNode);
}


DecisionNode::~DecisionNode()
{
}

void DecisionNode::ProcessNode(float dt)
{
	if (query())
		truePathNode->ProcessNode(dt);
	else
		falsePathNode->ProcessNode(dt);
}

void DecisionNode::SetQuery(DME::Query query)
{
	this->query = query;
}

void DecisionNode::SetTruePathNode(DecisionTreeNode* node)
{
	truePathNode = node;
}

void DecisionNode::SetFalsePathNode(DecisionTreeNode* node)
{
	falsePathNode = node;
}
