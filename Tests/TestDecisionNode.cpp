#include "CppUTest/TestHarness.h"
#include "DecisionNode.h"

class DecisionTreeNodeDeltaTimeSpy : public DecisionTreeNode
{
public:
	void ProcessNode(float dt) override
	{
		lastDeltaTime = dt;
	};

	float lastDeltaTime = 0;
};

TEST_GROUP(DecisionNode)
{
	DecisionNode decisionNode;
};

TEST(DecisionNode, DeltaTimeIsPropagatedToTruePathChild)
{
	DecisionTreeNodeDeltaTimeSpy truePathNodeSpy;
	decisionNode.SetQuery([]()->bool{return true; });
	decisionNode.SetTruePathNode(&truePathNodeSpy);

	decisionNode.ProcessNode(0.5);

	CHECK_EQUAL(0.5, truePathNodeSpy.lastDeltaTime);
}

TEST(DecisionNode, DeltaTimeIsPropagatedToFalsePathChild)
{
	DecisionTreeNodeDeltaTimeSpy falsePathNodeSpy;
	decisionNode.SetQuery([]()->bool{return false; });
	decisionNode.SetFalsePathNode(&falsePathNodeSpy);

	decisionNode.ProcessNode(0.5);

	CHECK_EQUAL(0.5, falsePathNodeSpy.lastDeltaTime);
}