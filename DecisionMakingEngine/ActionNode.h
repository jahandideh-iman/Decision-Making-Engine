#pragma once
#include "DecisionTreeNode.h"
#include "DMEDefines.h"



class ActionNode :
	public DecisionTreeNode
{

public:
	ActionNode(DME::UpdateAction updateAction = nullptr);
	~ActionNode();

	void SetAction(DME::UpdateAction updateAction);

	void ProcessNode(float dt) override;

private:
	DME::UpdateAction updateAction;
};

