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

	void CheckActionNode(ActionName expectedActionName, const DecisionTreeNode* node)
	{
		CHECK_TRUE(dynamic_cast<const ActionNode*>(node) != nullptr);
		CHECK_TRUE(dynamic_cast<const ActionNode*>(node)->GetActionName() == expectedActionName);
	}

	void CheckDecisionNode(ConditionName expectedConditionName, const DecisionTreeNode* node)
	{
		CHECK_TRUE(dynamic_cast<const DecisionNode*>(node) != nullptr);
		CHECK_TRUE(dynamic_cast<const DecisionNode*>(node)->GetConditionName() == expectedConditionName);
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

	CheckActionNode("ActionName", comp->GetRoot());

}

TEST(DecisionTreeParser, ComponentHasTheProvidedDecisionNodeAsRoot)
{
	comp = (DecisionTreeComponent*) parser.Create(
		"<DMEComponent  type=\"DecisionTree\" >"
		"     <Node type=\"DecisionNode\" >"
		"           <Condition>ConditionName</Condition>"
		"     </Node>"
		"</DMEComponent>");

	CheckDecisionNode("ConditionName", comp->GetRoot());
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

	CheckActionNode("TrueAction", root->GetTruePathNode());
	CheckActionNode("FalseAction", root->GetFalsePathNode());
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
	const DecisionNode* secondDecisionNode = dynamic_cast<const DecisionNode*>(root->GetFalsePathNode());

	CheckActionNode("FirstTrueAction", root->GetTruePathNode());
	CheckDecisionNode("FalsePathCondition", root->GetFalsePathNode());
	CheckActionNode("SecondTrueAction", secondDecisionNode->GetTruePathNode());
	CheckActionNode("SecondFalseAction", secondDecisionNode->GetFalsePathNode());
}