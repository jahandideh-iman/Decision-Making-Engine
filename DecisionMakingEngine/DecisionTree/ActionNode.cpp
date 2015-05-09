#include "ActionNode.h"


ActionNode::ActionNode(DecisionTreeComponent* owner, ActionName actionName) : DecisionTreeNode(owner)
{
	SetActionName(actionName);
}

ActionNode::~ActionNode()
{
}

void ActionNode::SetActionName(ActionName actionName)
{
	this->actionName = actionName;
}

void ActionNode::ProcessNode(float dt)
{
	if (actionName == "")
		return;

	owner->GetActionMethod(actionName)->Invoke(dt);
}

ActionName ActionNode::GetActionName() const
{
	return actionName;
}
