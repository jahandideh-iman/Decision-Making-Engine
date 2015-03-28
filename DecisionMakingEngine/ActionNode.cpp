#include "ActionNode.h"


ActionNode::ActionNode(DecisionTreeComponent* owner, ActionName updateActionName) : DecisionTreeNode(owner)
{
	this->updateActionName = updateActionName;
}


ActionNode::~ActionNode()
{
}

void ActionNode::SetActionName(ActionName updateActionName)
{
	owner->IsEmpty();
	this->updateActionName = updateActionName;
}

void ActionNode::ProcessNode(float dt)
{
	if (updateActionName == "")
		return;

	owner->GetActionMethod(updateActionName)(dt);
}

ActionName ActionNode::GetActionName() const
{
	return updateActionName;
}
