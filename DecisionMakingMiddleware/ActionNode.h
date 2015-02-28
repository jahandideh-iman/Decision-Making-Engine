#pragma once
#include "DecisionTreeNode.h"
#include <functional>

using std::function;



class ActionNode :
	public DecisionTreeNode
{
	typedef std::function<void()> Action;

public:
	ActionNode(Action action = nullptr);
	~ActionNode();

	void SetAction(Action action);

	void ProcessNode() override;

private:
	Action action;
};

