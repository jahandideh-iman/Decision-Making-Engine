#pragma once

class DecisionTreeNode
{
public:
	DecisionTreeNode();
	~DecisionTreeNode();

	virtual void ProcessNode(float dt) = 0;
};

