#include "ActionNode.h"


ActionNode::ActionNode(DME::UpdateAction updateAction)
{
	this->updateAction = updateAction;
}


ActionNode::~ActionNode()
{
}

void ActionNode::SetAction(DME::UpdateAction updateAction)
{
	this->updateAction = updateAction;
}

void ActionNode::ProcessNode(float dt)
{
	updateAction(dt);
}
