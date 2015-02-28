#include "ActionNode.h"


ActionNode::ActionNode(Action action)
{
	this->action = action;
}


ActionNode::~ActionNode()
{
}

void ActionNode::SetAction(Action action)
{
	this->action = action;
}

void ActionNode::ProcessNode()
{
	action();
}
