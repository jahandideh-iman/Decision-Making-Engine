#include "CppUTest/TestHarness.h"
#include "DecisionTreeComponent.h"
#include "ActionNode.h"
#include "DecisionNode.h"


TEST_GROUP(TestDecisionTreeComponent)
{
	DecisionTreeComponent component;

	void CallMultipleUpdate(unsigned numberOfTimes)
	{
		for (unsigned i = 0; i < numberOfTimes; ++i)
			component.Update();
	}
};

TEST(TestDecisionTreeComponent, IsEmptyOnCreation)
{
	CHECK_TRUE(component.IsEmpty());
}

TEST(TestDecisionTreeComponent, IsNotEmptyAfterSettingRoot)
{
	DecisionNode node;

	component.SetRoot(&node);

	CHECK_FALSE(component.IsEmpty());
}

TEST(TestDecisionTreeComponent, RootIsExecutedOnUpdateIfItIsAnActionNode)
{
	auto callCount = 0u;
	ActionNode actionNode([&]()->void{++callCount; });
	component.SetRoot(&actionNode);

	CallMultipleUpdate(5);

	CHECK_EQUAL(5, callCount);
}

TEST(TestDecisionTreeComponent, TruePathIsExecutedOnUpdateIfNodeConditionIsMet)
{
	auto callCount = 0u;

	ActionNode truePathNode([&]()->void{++callCount; });
	DecisionNode decisionNode([]()->bool{return true; }, &truePathNode);
	component.SetRoot(&decisionNode);

	CallMultipleUpdate(5);

	CHECK_EQUAL(5, callCount);
}

TEST(TestDecisionTreeComponent, FalsePathIsExecutedOnUpdateIfNodeConditionIsNotMet)
{
	auto callCount = 0u;

	ActionNode falsePathNode([&]()->void{++callCount; });
	DecisionNode decisionNode([]()->bool{return false; }, nullptr, &falsePathNode);
	component.SetRoot(&decisionNode);

	CallMultipleUpdate(5);

	CHECK_EQUAL(5, callCount);
}

TEST(TestDecisionTreeComponent, CompatibilityTest)
{
	auto callCount = 0u;
	ActionNode actionNode([&]()->void{++callCount; });
	DecisionNode secondDecisionNode([]()->bool{return false; }, nullptr, &actionNode);
	DecisionNode firstDecisionNode([]()->bool{return true; }, &secondDecisionNode, nullptr);
	component.SetRoot(&firstDecisionNode);

	CallMultipleUpdate(5);

	CHECK_EQUAL(5, callCount);
}

