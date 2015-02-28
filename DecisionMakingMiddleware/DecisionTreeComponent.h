#pragma once

#include "DecisionTreeNode.h"


class DecisionTreeComponent
{
public:
	DecisionTreeComponent();
	~DecisionTreeComponent();

	void Update();

	void SetRoot(DecisionTreeNode* root);

	bool IsEmpty();

private:
	DecisionTreeNode* root = nullptr;
};

