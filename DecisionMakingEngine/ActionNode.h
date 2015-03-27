#pragma once
#include "DecisionTreeNode.h"
#include "DMEDefines.h"

using DME::ActionName;

class ActionNode :
	public DecisionTreeNode
{

public:
	ActionNode(DecisionTreeComponent* owner, ActionName updateAction = "");
	~ActionNode();

	void SetActionName(ActionName updateAction);
	ActionName GetAction() const;

	void ProcessNode(float dt) override;

private:
	ActionName updateActionName;
};

