#pragma once
#include "DecisionTreeNode.h"
#include <functional>

using std::function;



class DecisionNode :
	public DecisionTreeNode
{
	typedef function<bool()> Query;

public:
	DecisionNode(Query query = nullptr, DecisionTreeNode* truePathNode = nullptr, DecisionTreeNode* falsePathNode = nullptr);
	~DecisionNode();

	void ProcessNode() override;

	void SetTruePathNode(DecisionTreeNode* node);
	void SetFalsePathNode(DecisionTreeNode* node);
	void SetQuery(Query query);
private:
	DecisionTreeNode* truePathNode = nullptr;
	DecisionTreeNode* falsePathNode = nullptr;
	Query query = nullptr;
};

