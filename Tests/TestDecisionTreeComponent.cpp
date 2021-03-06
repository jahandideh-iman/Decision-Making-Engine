#include "CppUTest/TestHarness.h"
#include "DecisionTree/DecisionTreeComponent.h"
#include "DecisionTree/ActionNode.h"
#include "DecisionTree/DecisionNode.h"

#include "Factories/InterfaceFactory.h"

using DME::InterfaceFactory;


class DecisionNodeDeltaTimeSpy : public DecisionNode
{
public:
	DecisionNodeDeltaTimeSpy(DecisionTreeComponent*owner):DecisionNode(owner)
	{
	}

	void ProcessNode(float dt) override
	{
		lastDeltaTime = dt;
	}

	float lastDeltaTime = 0;
};

TEST_GROUP(DecisionTreeComponent)
{
	DecisionTreeComponent* decisionTreeComponent = nullptr;

	void setup()
	{
		decisionTreeComponent = new DecisionTreeComponent();
	}

	void teardown()
	{
		delete decisionTreeComponent;
	}

	void CallMultipleUpdate(unsigned numberOfTimes)
	{
		for (unsigned i = 0; i < numberOfTimes; ++i)
			decisionTreeComponent->Update();
	}

	ActionNode* CreateActionNode(ActionName actionName, Action* action)
	{
		decisionTreeComponent->SetActionMethod(actionName, action);
		return new ActionNode(decisionTreeComponent, actionName);
	}

	DecisionNode* CreateDecisionNode(ConditionName conditionName, Condition* condition, DecisionTreeNode* truePathNode = nullptr , DecisionTreeNode* falsePathNode = nullptr)
	{
		decisionTreeComponent->SetConditionMethod(conditionName, condition);
		return new DecisionNode(decisionTreeComponent, conditionName, truePathNode, falsePathNode);
	}
};

TEST(DecisionTreeComponent, IsEmptyOnCreation)
{
	CHECK_TRUE(decisionTreeComponent->IsEmpty());
}

TEST(DecisionTreeComponent, IsNotEmptyAfterSettingRoot)
{
	DecisionNode* node = new DecisionNode(decisionTreeComponent);

	decisionTreeComponent->SetRoot(node);

	CHECK_FALSE(decisionTreeComponent->IsEmpty());
}

TEST(DecisionTreeComponent, RootIsExecutedOnUpdateIfItIsAnActionNode)
{
	auto callCount = 0u;
	ActionNode* actionNode = CreateActionNode("ArbitraryName", InterfaceFactory::CreateUpdateAction([&](float dt)->void{++callCount; }));
	decisionTreeComponent->SetRoot(actionNode);

	CallMultipleUpdate(5);

	CHECK_EQUAL(5, callCount);
}

TEST(DecisionTreeComponent, TruePathIsExecutedOnUpdateIfNodeConditionIsMet)
{
	auto callCount = 0u;

	ActionNode* truePathNode = CreateActionNode("ArbitraryActionName", InterfaceFactory::CreateUpdateAction([&](float dt)->void{++callCount; }));
	DecisionNode* decisionNode = CreateDecisionNode("ArbitraryConditionName", InterfaceFactory::CreateCondition([]()->bool{return true; }), truePathNode);
	decisionTreeComponent->SetRoot(decisionNode);

	CallMultipleUpdate(5);

	CHECK_EQUAL(5, callCount);
}

TEST(DecisionTreeComponent, FalsePathIsExecutedOnUpdateIfNodeConditionIsNotMet)
{
	auto callCount = 0u;

	ActionNode* falsePathNode = CreateActionNode("ArbitraryActionName", InterfaceFactory::CreateUpdateAction([&](float dt)->void{++callCount; }));
	DecisionNode* decisionNode = CreateDecisionNode("ArbitraryConditionName", InterfaceFactory::CreateCondition([]()->bool{return false; }), nullptr, falsePathNode);
	decisionTreeComponent->SetRoot(decisionNode);

	CallMultipleUpdate(5);

	CHECK_EQUAL(5, callCount);
}

TEST(DecisionTreeComponent, DeltaTimeIsPropagatedToDecisionNode)
{
	DecisionNodeDeltaTimeSpy* decisionNodeSpy = new DecisionNodeDeltaTimeSpy(decisionTreeComponent);
	decisionTreeComponent->SetRoot(decisionNodeSpy);

	decisionTreeComponent->Update(0.5);

	CHECK_EQUAL(0.5, decisionNodeSpy->lastDeltaTime)
}

TEST(DecisionTreeComponent, IntegerationTest)
{
	auto callCount = 0u;
	ActionNode* actionNode = CreateActionNode("ArbitraryActionName", InterfaceFactory::CreateUpdateAction([&](float dt)->void{++callCount; }));
	DecisionNode* secondDecisionNode = CreateDecisionNode("ConditionOne", InterfaceFactory::CreateCondition([]()->bool{return false; }), nullptr, actionNode);
	DecisionNode* firstDecisionNode = CreateDecisionNode("ConditionTwo", InterfaceFactory::CreateCondition([]()->bool{return true; }), secondDecisionNode, nullptr);
	decisionTreeComponent->SetRoot(firstDecisionNode);

	CallMultipleUpdate(5);

	CHECK_EQUAL(5, callCount);
}