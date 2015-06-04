#include "CppUTest/TestHarness.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeParser.h"
#include "BehaviorTree/BehaviorTask.h"
#include "BehaviorTree/ActionTask.h"
#include "BehaviorTree/SequenceTask.h"
#include "BehaviorTree/SelectorTask.h"




TEST_GROUP(BehaviorTreeParser)
{
	BehaviorTreeParser parser;
	BehaviorTreeComponent *comp = nullptr;

	void teardown()
	{
		delete comp;
	}

	void CheckActionTask(DME::ActionName expectedActionName, const BehaviorTask* task)
	{
		CHECK_TRUE(dynamic_cast<const ActionTask*>(task) != nullptr);
		CHECK_TRUE(dynamic_cast<const ActionTask*>(task)->GetTaskName() == expectedActionName);
	}

	void CheckSequenceTask(const BehaviorTask* task)
	{
		CHECK_TRUE(dynamic_cast<const SequenceTask*>(task) != nullptr);
	}

	void CheckSelectorTask(const BehaviorTask* task)
	{
		CHECK_TRUE(dynamic_cast<const SelectorTask*>(task) != nullptr);
	}
};

TEST(BehaviorTreeParser, CreateNullOnEmptyInput)
{
	BehaviorTreeComponent *comp = (BehaviorTreeComponent*)parser.Create("");

	POINTERS_EQUAL(nullptr, comp);
}

TEST(BehaviorTreeParser, CreateEmptyComponentWithNoData)
{
	comp = (BehaviorTreeComponent*)parser.Create(
		"<DMEComponent  type=\"BehaviorTree\" >"
		"</DMEComponent> ");

	CHECK_TRUE(comp->IsEmpty());
}

TEST(BehaviorTreeParser, ComponentHasTheProvidedActionTaskAsRoot)
{
	comp = (BehaviorTreeComponent *)parser.Create(
		"<DMEComponent  type=\"BehaviorTree\" >"
		"     <Task type=\"ActionTask\" >"
		"           <Action>ActionName</Action>"
		"     </Task>"
		"</DMEComponent>");

	CheckActionTask("ActionName", comp->GetRoot());
}

TEST(BehaviorTreeParser, ComponentHasTheProvidedSequenceTaskAsRoot)
{
	comp = (BehaviorTreeComponent *)parser.Create(
		"<DMEComponent  type=\"BehaviorTree\" >"
		"     <Task type=\"SequenceTask\" >"
		"     </Task>"
		"</DMEComponent>");

	CheckSequenceTask(comp->GetRoot());
}

TEST(BehaviorTreeParser, ProvidedSequenceTaskHasItsChildren)
{
	comp = (BehaviorTreeComponent *)parser.Create(
		"<DMEComponent  type=\"BehaviorTree\" >"
		"     <Task type=\"SequenceTask\" >"
		"          <Child>"
		"               <Task type=\"ActionTask\" >"
		"                    <Action>ActionName</Action>"
		"               </Task>"
		"          </Child>"
		"          <Child>"
		"               <Task type=\"SequenceTask\" >"
		"               </Task>"
		"          </Child>"
		"     </Task>"
		"</DMEComponent>");

	auto root = (SequenceTask*) comp->GetRoot();

	CheckSequenceTask(root);
	CheckActionTask("ActionName", root->GetChild(0));
	CheckSequenceTask(root->GetChild(1));
}

TEST(BehaviorTreeParser, ComponentHasTheProvidedSelectorTaskAsRoot)
{
	comp = (BehaviorTreeComponent *)parser.Create(
		"<DMEComponent  type=\"BehaviorTree\" >"
		"     <Task type=\"SelectorTask\" >"
		"     </Task>"
		"</DMEComponent>");

	CheckSelectorTask(comp->GetRoot());
}

TEST(BehaviorTreeParser, ProvidedSelectorTaskHasItsChildren)
{
	comp = (BehaviorTreeComponent *)parser.Create(
		"<DMEComponent  type=\"BehaviorTree\" >"
		"     <Task type=\"SelectorTask\" >"
		"          <Child>"
		"               <Task type=\"ActionTask\" >"
		"                    <Action>ActionName</Action>"
		"               </Task>"
		"          </Child>"
		"          <Child>"
		"               <Task type=\"SelectorTask\" >"
		"               </Task>"
		"          </Child>"
		"     </Task>"
		"</DMEComponent>");

	auto root = (SelectorTask*)comp->GetRoot();

	CheckSelectorTask(root);
	CheckActionTask("ActionName", root->GetChild(0));
	CheckSelectorTask(root->GetChild(1));
}

TEST(BehaviorTreeParser, Integration)
{
	comp = (BehaviorTreeComponent *)parser.Create(
		"<DMEComponent  type=\"BehaviorTree\" >"
		"     <Task type=\"SelectorTask\" >"
		"          <Child>"
		"               <Task type=\"SelectorTask\" >"
		"                     <Child>"
		"                         <Task type=\"ActionTask\" >"
		"                              <Action>Sel_Sel_0_ActionName</Action>"
		"                          </Task>"
		"                     </Child>"
		"                     <Child>"
		"                         <Task type=\"ActionTask\" >"
		"                              <Action>Sel_Sel_1_ActionName</Action>"
		"                          </Task>"
		"                     </Child>"
		"               </Task>"
		"          </Child>"
		"          <Child>"
		"               <Task type=\"SequenceTask\" >"
		"                     <Child>"
		"                         <Task type=\"ActionTask\" >"
		"                              <Action>Sel_Seq_0_ActionName</Action>"
		"                          </Task>"
		"                     </Child>"
		"                     <Child>"
		"                         <Task type=\"ActionTask\" >"
		"                              <Action>Sel_Seq_1_ActionName</Action>"
		"                          </Task>"
		"                     </Child>"
		"               </Task>"
		"          </Child>"
		"     </Task>"
		"</DMEComponent>");

	auto root = (SelectorTask*)comp->GetRoot();
	auto child0 = (SelectorTask*)root->GetChild(0);
	auto child1 = (SequenceTask*)root->GetChild(1);

	CheckSelectorTask(root);

	CheckSelectorTask(child0);
	CheckActionTask("Sel_Sel_0_ActionName", child0->GetChild(0));
	CheckActionTask("Sel_Sel_1_ActionName", child0->GetChild(1));

	CheckSequenceTask(child1);
	CheckActionTask("Sel_Seq_0_ActionName", child1->GetChild(0));
	CheckActionTask("Sel_Seq_1_ActionName", child1->GetChild(1));
}