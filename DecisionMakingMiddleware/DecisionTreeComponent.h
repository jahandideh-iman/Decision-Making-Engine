#pragma once

#include "DecisionTreeNode.h"
#include "AIComponent.h"


class DecisionTreeComponent : public AIComponent
{
public:
	DecisionTreeComponent();
	~DecisionTreeComponent();

	void Update(float dt = 0) override;

	void SetRoot(DecisionTreeNode* root);

	bool IsEmpty();

private:
	DecisionTreeNode* root = nullptr;
};

