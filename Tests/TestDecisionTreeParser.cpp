#include "CppUTest/TestHarness.h"
#include "DecisionTreeParser.h"
#include "ActionNode.h"
#include "DecisionNode.h"
#include <sstream>

using std::string;

#define SAFE_DELETE(pointer) {if (pointer) delete pointer; pointer = nullptr; }



TEST_GROUP(DecisionTreeParser)
{
	DecisionTreeComponent* comp;
	std::stringbuf* tempBuf = nullptr;
	std::istream* tempIStream = nullptr;

	void teardown()
	{
		SAFE_DELETE(comp);
		SAFE_DELETE(tempBuf);
		SAFE_DELETE(tempIStream);
	}

	std::istream& CreateStream(string input)
	{
		tempBuf = new std::stringbuf(input);
		tempIStream = new std::istream(tempBuf);
		return  *(tempIStream);
	}
};

TEST(DecisionTreeParser, CreateNullOnEmptyInput)
{
	comp = DecisionTreeParser::Create(CreateStream(""));

	POINTERS_EQUAL(nullptr, comp);
}

TEST(DecisionTreeParser, CreateEmptyComponentWithNoData)
{
	comp = DecisionTreeParser::Create(CreateStream(
		"<DMEComponent  type=\"DecisionTree\" >"
		"</DMEComponent>"));

	CHECK_TRUE(comp->IsEmpty());
}

TEST(DecisionTreeParser, ComponentHasTheProvidedActionNodeAsRoot)
{
	comp = DecisionTreeParser::Create(CreateStream(
		"<DMEComponent  type=\"DecisionTree\" >"
		"     <Node type=\"ActionNode\" >"
		"           <Action>ActionName</Action>"
		"     </Node>"
		"</DMEComponent>"));

	CHECK_TRUE(comp->GetRoot() != nullptr);
	CHECK_TRUE(dynamic_cast<const ActionNode*>(comp->GetRoot()) != nullptr);
	CHECK_TRUE(dynamic_cast<const ActionNode*>(comp->GetRoot())->GetActionName() == "ActionName");
}

TEST(DecisionTreeParser, ComponentHasTheProvidedDecisionNodeAsRoot)
{
	comp = DecisionTreeParser::Create(CreateStream(
		"<DMEComponent  type=\"DecisionTree\" >"
		"     <Node type=\"DecisionNode\" >"
		"           <Condition>ConditionName</Condition>"
		"     </Node>"
		"</DMEComponent>"));

	CHECK_TRUE(comp->GetRoot() != nullptr);
	CHECK_TRUE(dynamic_cast<const DecisionNode*>(comp->GetRoot()) != nullptr);
	CHECK_TRUE(dynamic_cast<const DecisionNode*>(comp->GetRoot())->GetConditionName() == "ConditionName");
}

TEST(DecisionTreeParser, ComponentHasTheProvidedTrueAndFalsePathChild)
{
	comp = DecisionTreeParser::Create(CreateStream(
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
		"</DMEComponent>"));

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
	comp = DecisionTreeParser::Create(CreateStream(
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
		"</DMEComponent>"));

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