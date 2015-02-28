#pragma once

class DecisionTreeNode
{
public:
	DecisionTreeNode();
	~DecisionTreeNode();

	virtual void ProcessNode() = 0;
};

