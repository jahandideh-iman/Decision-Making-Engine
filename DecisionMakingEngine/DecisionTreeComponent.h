#pragma once

#include <map>
#include "DMEComponent.h"
#include "DMEDefines.h"
#include "DMEUtilities.h"
#include "Condition.h"
#include "EveryUpdateCalledAction.h"

using DME::ActionName;
using DME::EveryUpdateCalledAction;
using DME::ConditionName;
using DME::Condition;

class DecisionTreeNode;

class DecisionTreeComponent : public DMEComponent
{
	typedef std::map<ActionName, EveryUpdateCalledAction*> ActionContainer;
	typedef std::map<ConditionName, Condition*> ConditionContainer;

public:
	DecisionTreeComponent(DecisionTreeNode* root = nullptr);
	~DecisionTreeComponent();

	void Update(float dt = 0) override;

	void SetRoot(DecisionTreeNode* root);
	const DecisionTreeNode* GetRoot() const; 

	void AddAction(ActionName actionName);
	void SetActionMethod(ActionName actionName, EveryUpdateCalledAction* action);
	const EveryUpdateCalledAction* GetActionMethod(ActionName actionName) const;

	void AddCondition(ConditionName conditionName);	
	void SetConditionMethod(ConditionName conditionName, Condition* condition);
	const Condition* GetConditionMethod(ConditionName conditionName) const;

	bool IsEmpty() const;

private:
	DecisionTreeNode* root = nullptr;

	ActionContainer actions;
	ConditionContainer conditions;
};

