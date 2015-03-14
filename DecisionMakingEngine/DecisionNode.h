#pragma once
#include "DecisionTreeNode.h"
#include <functional>

#include "DMEDefines.h"

using std::function;



class DecisionNode :
	public DecisionTreeNode
{
public:
	DecisionNode(DME::Query query = nullptr, DecisionTreeNode* truePathNode = nullptr, DecisionTreeNode* falsePathNode = nullptr);
	~DecisionNode();

	void ProcessNode(float dt) override;

	void SetTruePathNode(DecisionTreeNode* node);
	void SetFalsePathNode(DecisionTreeNode* node);
	void SetQuery(DME::Query query);
private:
	DecisionTreeNode* truePathNode = nullptr;
	DecisionTreeNode* falsePathNode = nullptr;
	DME::Query query = nullptr;
};

