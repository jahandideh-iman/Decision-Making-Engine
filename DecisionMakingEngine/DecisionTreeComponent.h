#pragma once

#include "DecisionTreeNode.h"
#include "DMEComponent.h"


class DecisionTreeComponent : public DMEComponent
{
public:
	DecisionTreeComponent(DecisionTreeNode* root = nullptr);
	~DecisionTreeComponent();

	void Update(float dt = 0) override;

	void SetRoot(DecisionTreeNode* root);

	bool IsEmpty();

private:
	DecisionTreeNode* root = nullptr;
};

