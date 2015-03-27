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
	CHECK_TRUE(dynamic_cast<const ActionNode*>(comp->GetRoot())->GetAction() == "ActionName");
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