#pragma once
#include "DecisionTreeNode.h"

#include "DMEDefines.h"
#include "DMEUtilities.h"
#include "Condition.h"
 
using DME::ConditionName;
using DME::Condition;

class DecisionNode :
	public DecisionTreeNode
{
public:
	DecisionNode(DecisionTreeComponent* owner, ConditionName conditionName = "", DecisionTreeNode* truePathNode = nullptr, DecisionTreeNode* falsePathNode = nullptr);
	~DecisionNode();

	void ProcessNode(float dt) override;

	void SetTruePathNode(DecisionTreeNode* node);
	void SetFalsePathNode(DecisionTreeNode* node);
	void SetConditionName(ConditionName conditionName);
	ConditionName GetConditionName() const;

	const DecisionTreeNode* GetTruePathNode() const;
	const DecisionTreeNode* GetFalsePathNode() const;

private:
	DecisionTreeNode* truePathNode = nullptr;
	DecisionTreeNode* falsePathNode = nullptr;
	ConditionName conditionName;
};

