#include "DecisionNode.h"


DecisionNode::DecisionNode(Query query, DecisionTreeNode* truePathNode, DecisionTreeNode* falsePathNode)
{
	SetQuery(query);
	SetTruePathNode(truePathNode);
	SetFalsePathNode(falsePathNode);
}


DecisionNode::~DecisionNode()
{
}

void DecisionNode::ProcessNode()
{
	if (query())
		truePathNode->ProcessNode();
	else
		falsePathNode->ProcessNode();
}

void DecisionNode::SetQuery(Query query)
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
