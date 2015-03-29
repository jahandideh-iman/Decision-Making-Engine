#include "CppUTest/TestHarness.h"
#include "DecisionTreeParser.h"
#include "ActionNode.h"
#include "DecisionNode.h"
#include <sstream>

using std::string;




TEST_GROUP(DecisionTreeParser)
{
	DecisionTreeComponent* comp;
	DecisionTreeParser parser;


	void teardown()
	{
		SAFE_DELETE(comp);

	}

};

TEST(DecisionTreeParser, CreateNullOnEmptyInput)
{
	comp = (DecisionTreeComponent*) parser.Create("");

	POINTERS_EQUAL(nullptr, comp);
}

TEST(DecisionTreeParser, CreateEmptyComponentWithNoData)
{
	comp = (DecisionTreeComponent*) parser.Create(
		"<DMEComponent  type=\"DecisionTree\" >"
		"</DMEComponent> ");

	CHECK_TRUE(comp->IsEmpty());
}

TEST(DecisionTreeParser, ComponentHasTheProvidedActionNodeAsRoot)
{
	comp = (DecisionTreeComponent*) parser.Create(
		"<DMEComponent  type=\"DecisionTree\" >"
		"     <Node type=\"ActionNode\" >"
		"           <Action>ActionName</Action>"
		"     </Node>"
		"</DMEComponent>");

	CHECK_TRUE(comp->GetRoot() != nullptr);
	CHECK_TRUE(dynamic_cast<const ActionNode*>(comp->GetRoot()) != nullptr);
	CHECK_TRUE(dynamic_cast<const ActionNode*>(comp->GetRoot())->GetActionName() == "ActionName");
}

TEST(DecisionTreeParser, ComponentHasTheProvidedDecisionNodeAsRoot)
{
	comp = (DecisionTreeComponent*) parser.Create(
		"<DMEComponent  type=\"DecisionTree\" >"
		"     <Node type=\"DecisionNode\" >"
		"           <Condition>ConditionName</Condition>"
		"     </Node>"
		"</DMEComponent>");

	CHECK_TRUE(comp->GetRoot() != nullptr);
	CHECK_TRUE(dynamic_cast<const DecisionNode*>(comp->GetRoot()) != nullptr);
	CHECK_TRUE(dynamic_cast<const DecisionNode*>(comp->GetRoot())->GetConditionName() == "ConditionName");
}

TEST(DecisionTreeParser, ComponentHasTheProvidedTrueAndFalsePathChild)
{
	comp = (DecisionTreeComponent*) parser.Create(
		"<DMEComponent  type=\"DecisionTree\" >"
		"     <Node type=\"DecisionNode\" >"
		"           <Condition>ConditionName</Condition>"
		"           <TruePath>"
		"                <Node type=\"ActionNode\" >"
		"                      <Action>TrueAction</Action>"
		"                </Node>"
		"           </TruePath>"
		"            <FalsePath>"
		"                <Node type=\"ActionNode\" >"
		"                      <Action>FalseAction</Action>"
		"                </Node>"
		"          </FalsePath>"
		"     </Node>"
		"</DMEComponent>");

	const DecisionNode* root = dynamic_cast<const DecisionNode*>(comp->GetRoot());
	const ActionNode* truePathNode = dynamic_cast<const ActionNode*>(root->GetTruePathNode());
	const ActionNode* falsePathNode = dynamic_cast<const ActionNode*>(root->GetFalsePathNode());

	CHECK_TRUE(truePathNode != nullptr);
	CHECK_TRUE(truePathNode->GetActionName() == "TrueAction");
	
	CHECK_TRUE(falsePathNode != nullptr);
	CHECK_TRUE(falsePathNode->GetActionName() == "FalseAction");
}

TEST(DecisionTreeParser, IntegrationTest)
{
	comp = (DecisionTreeComponent*) parser.Create(
		"<DMEComponent  type=\"DecisionTree\" >"
		"     <Node type=\"DecisionNode\" >"
		"           <Condition>FirstConditionName</Condition>"
		"           <TruePath>"
		"                <Node type=\"ActionNode\" >"
		"                      <Action>FirstTrueAction</Action>"
		"                </Node>"
		"           </TruePath>"
		"            <FalsePath>"
		"                  <Node type=\"DecisionNode\" >"
		"                      <Condition>FalsePathCondition</Condition>"
		"                      <TruePath>"
		"                           <Node type=\"ActionNode\" >"
		"                               <Action>SecondTrueAction</Action>"
		"                           </Node>"
		"                      </TruePath>"
		"                      <FalsePath>"
		"                          <Node type=\"ActionNode\" >"
		"                                <Action>SecondFalseAction</Action>"
		"                          </Node>"
		"                      </FalsePath>"
		"                 </Node>"
		"          </FalsePath>"
		"     </Node>"
		"</DMEComponent>");

	const DecisionNode* root = dynamic_cast<const DecisionNode*>(comp->GetRoot());
	const ActionNode* firstTruePathNode = dynamic_cast<const ActionNode*>(root->GetTruePathNode());
	const DecisionNode* firstFalsePathNode = dynamic_cast<const DecisionNode*>(root->GetFalsePathNode());

	const ActionNode* secondTruePathNode = dynamic_cast<const ActionNode*>(firstFalsePathNode->GetTruePathNode());
	const ActionNode* secondFalsePathNode = dynamic_cast<const ActionNode*>(firstFalsePathNode->GetFalsePathNode());



	CHECK_TRUE(firstTruePathNode != nullptr);
	CHECK_TRUE(firstTruePathNode->GetActionName() == "FirstTrueAction");

	CHECK_TRUE(firstFalsePathNode != nullptr);
	CHECK_TRUE(firstFalsePathNode->GetConditionName() == "FalsePathCondition");

	CHECK_TRUE(secondTruePathNode != nullptr);
	CHECK_TRUE(secondTruePathNode->GetActionName() == "SecondTrueAction");

	CHECK_TRUE(secondFalsePathNode != nullptr);
	CHECK_TRUE(secondFalsePathNode->GetActionName() == "SecondFalseAction");
}