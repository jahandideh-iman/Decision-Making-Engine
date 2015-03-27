#pragma once

#include <map>
#include "DMEComponent.h"
#include "DMEDefines.h"

using DME::ActionName;
using DME::UpdateAction;
using DME::ConditionName;
using DME::Condition;

class DecisionTreeNode;

class DecisionTreeComponent : public DMEComponent
{
	typedef std::map<ActionName, UpdateAction> ActionContainer;
	typedef std::map<ConditionName, Condition> ConditionContainer;

public:
	DecisionTreeComponent(DecisionTreeNode* root = nullptr);
	~DecisionTreeComponent();

	void Update(float dt = 0) override;

	void SetRoot(DecisionTreeNode* root);

	const DecisionTreeNode* GetRoot() const; 

	void AddAction(ActionName actionName);
	void SetActionMethod(ActionName actionName, UpdateAction action);
	UpdateAction GetActionMethod(ActionName actionName);

	void AddCondition(ConditionName conditionName);	
	void SetConditionMethod(ConditionName conditionName, Condition condition);
	Condition GetConditionMethod(ConditionName conditionName);

	bool IsEmpty() const;

private:
	DecisionTreeNode* root = nullptr;

	ActionContainer actions;
	ConditionContainer conditions;
};

