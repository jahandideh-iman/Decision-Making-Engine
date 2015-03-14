#include "DecisionTreeComponent.h"


DecisionTreeComponent::DecisionTreeComponent(DecisionTreeNode* root)
{
	SetRoot(root);
}


DecisionTreeComponent::~DecisionTreeComponent()
{
}

bool DecisionTreeComponent::IsEmpty()
{
	return root == nullptr;
}

void DecisionTreeComponent::SetRoot(DecisionTreeNode* root)
{
	this->root = root;
}

void DecisionTreeComponent::Update(float dt)
{
	root->ProcessNode(dt);
}
