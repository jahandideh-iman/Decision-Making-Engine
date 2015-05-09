#pragma once
#include "DecisionTreeNode.h"
#include "Core/DMEDefines.h"


class ActionNode :
	public DecisionTreeNode
{

public:
	ActionNode(DecisionTreeComponent* owner, DME::ActionName actionName = "");
	~ActionNode();

	void SetActionName(DME::ActionName actionName);
	DME::ActionName GetActionName() const;

	void ProcessNode(float dt) override;

private:
	DME::ActionName actionName;
};

