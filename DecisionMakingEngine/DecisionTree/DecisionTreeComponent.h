#pragma once


#include "Core/DMEComponent.h"
#include "Core/DMEDefines.h"


namespace DME
{
	class Condition;
	class Action;
}

using DME::ActionName;
using DME::ConditionName;
using DME::Action;
using DME::Condition;

class DecisionTreeNode;

class DecisionTreeComponent : public DMEComponent
{

public:
	DecisionTreeComponent(DecisionTreeNode* root = nullptr);
	~DecisionTreeComponent();

	void Update(float dt = 0) override;

	void SetRoot(DecisionTreeNode* root);
	const DecisionTreeNode* GetRoot() const; 

	void AddAction(ActionName actionName);
	void SetActionMethod(ActionName actionName, DME::Action* action);
	const DME::Action* GetActionMethod(ActionName actionName) const;

	void AddCondition(ConditionName conditionName);	
	void SetConditionMethod(ConditionName conditionName, Condition* condition);
	const Condition* GetConditionMethod(ConditionName conditionName) const;

	bool IsEmpty() const;

private:
	DecisionTreeNode* root = nullptr;
};

