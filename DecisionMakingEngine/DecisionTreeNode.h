#pragma once

#include "DecisionTreeComponent.h"

class DecisionTreeNode
{
public:
	DecisionTreeNode(DecisionTreeComponent* owner);
	virtual ~DecisionTreeNode() = 0;

	virtual void ProcessNode(float dt) = 0;
protected:
	DecisionTreeComponent * owner = nullptr;
};

