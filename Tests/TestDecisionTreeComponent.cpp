#include "CppUTest/TestHarness.h"
#include "DecisionTreeComponent.h"
#include "ActionNode.h"
#include "DecisionNode.h"


class DecisionNodeDeltaTimeSpy : public DecisionNode
{
public:
	void ProcessNode(float dt) override
	{
		lastDeltaTime = dt;
	}

	float lastDeltaTime = 0;
};

TEST_GROUP(DecisionTreeComponent)
{
	DecisionTreeComponent decisionTreeComponent;

	void CallMultipleUpdate(unsigned numberOfTimes)
	{
		for (unsigned i = 0; i < numberOfTimes; ++i)
			decisionTreeComponent.Update();
	}
};

TEST(DecisionTreeComponent, IsEmptyOnCreation)
{
	CHECK_TRUE(decisionTreeComponent.IsEmpty());
}

TEST(DecisionTreeComponent, IsNotEmptyAfterSettingRoot)
{
	DecisionNode node;

	decisionTreeComponent.SetRoot(&node);

	CHECK_FALSE(decisionTreeComponent.IsEmpty());
}

TEST(DecisionTreeComponent, RootIsExecutedOnUpdateIfItIsAnActionNode)
{
	auto callCount = 0u;
	ActionNode actionNode([&](float dt)->void{++callCount; });
	decisionTreeComponent.SetRoot(&actionNode);

	CallMultipleUpdate(5);

	CHECK_EQUAL(5, callCount);
}

TEST(DecisionTreeComponent, TruePathIsExecutedOnUpdateIfNodeConditionIsMet)
{
	auto callCount = 0u;

	ActionNode truePathNode([&](float dt)->void{++callCount; });
	DecisionNode decisionNode([]()->bool{return true; }, &truePathNode);
	decisionTreeComponent.SetRoot(&decisionNode);

	CallMultipleUpdate(5);

	CHECK_EQUAL(5, callCount);
}

TEST(DecisionTreeComponent, FalsePathIsExecutedOnUpdateIfNodeConditionIsNotMet)
{
	auto callCount = 0u;

	ActionNode falsePathNode([&](float dt)->void{++callCount; });
	DecisionNode decisionNode([]()->bool{return false; }, nullptr, &falsePathNode);
	decisionTreeComponent.SetRoot(&decisionNode);

	CallMultipleUpdate(5);

	CHECK_EQUAL(5, callCount);
}

TEST(DecisionTreeComponent, DeltaTimeIsPropagatedToDecisionNode)
{
	DecisionNodeDeltaTimeSpy decisionNodeSpy;
	decisionTreeComponent.SetRoot(&decisionNodeSpy);

	decisionTreeComponent.Update(0.5);

	CHECK_EQUAL(0.5, decisionNodeSpy.lastDeltaTime)
}

TEST(DecisionTreeComponent, CompatibilityTest)
{
	auto callCount = 0u;
	ActionNode actionNode([&](float dt)->void{++callCount; });
	DecisionNode secondDecisionNode([]()->bool{return false; }, nullptr, &actionNode);
	DecisionNode firstDecisionNode([]()->bool{return true; }, &secondDecisionNode, nullptr);
	decisionTreeComponent.SetRoot(&firstDecisionNode);

	CallMultipleUpdate(5);

	CHECK_EQUAL(5, callCount);
}



