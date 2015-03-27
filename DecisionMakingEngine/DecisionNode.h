#pragma once
#include "DecisionTreeNode.h"
#include <functional>

#include "DMEDefines.h"
#include "DMEUtilities.h"
 
using DME::ConditionName;
using DME::Condition;
using std::function;



class DecisionNode :
	public DecisionTreeNode
{
public:
	DecisionNode(DecisionTreeComponent* owner = nullptr, ConditionName conditionName = "", DecisionTreeNode* truePathNode = nullptr, DecisionTreeNode* falsePathNode = nullptr);
	~DecisionNode();

	void ProcessNode(float dt) override;

	void SetTruePathNode(DecisionTreeNode* node);
	void SetFalsePathNode(DecisionTreeNode* node);
	void SetConditionName(ConditionName conditionName);
	ConditionName GetConditionName() const;

private:
	DecisionTreeNode* truePathNode = nullptr;
	DecisionTreeNode* falsePathNode = nullptr;
	ConditionName conditionName;
};

