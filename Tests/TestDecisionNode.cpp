#include "CppUTest/TestHarness.h"
#include "DecisionNode.h"

class DecisionTreeNodeDeltaTimeSpy : public DecisionTreeNode
{
public:
	DecisionTreeNodeDeltaTimeSpy() : DecisionTreeNode(nullptr)
	{
	}

	~DecisionTreeNodeDeltaTimeSpy()
	{
	}

	void ProcessNode(float dt) override
	{
		lastDeltaTime = dt;
	};

	float lastDeltaTime = 0;
};

TEST_GROUP(DecisionNode)
{
	DecisionTreeComponent* comp = nullptr;
	DecisionNode* decisionNode = nullptr;

	void setup()
	{
		comp = new DecisionTreeComponent();
		decisionNode = new DecisionNode(comp);
		comp->AddCondition("Condition");
		decisionNode->SetConditionName("Condition");
	}

	void teardown()
	{
		delete decisionNode;
		delete comp;
	}
};

TEST(DecisionNode, DeltaTimeIsPropagatedToTruePathChild)
{
	DecisionTreeNodeDeltaTimeSpy* truePathNodeSpy = new DecisionTreeNodeDeltaTimeSpy;
	comp->SetConditionMethod("Condition",new Condition([]()->bool{return true; }));
	decisionNode->SetTruePathNode(truePathNodeSpy);
				
	decisionNode->ProcessNode(0.5);

	CHECK_EQUAL(0.5, truePathNodeSpy->lastDeltaTime);
}

TEST(DecisionNode, DeltaTimeIsPropagatedToFalsePathChild)
{
	DecisionTreeNodeDeltaTimeSpy* falsePathNodeSpy = new DecisionTreeNodeDeltaTimeSpy;
	comp->SetConditionMethod("Condition", new Condition([]()->bool{return false; }));
	decisionNode->SetFalsePathNode(falsePathNodeSpy);

	decisionNode->ProcessNode(0.5);

	CHECK_EQUAL(0.5, falsePathNodeSpy->lastDeltaTime);
}