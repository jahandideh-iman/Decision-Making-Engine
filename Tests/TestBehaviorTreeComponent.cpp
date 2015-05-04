#include "CppUTest/TestHarness.h"
#include "BehaviorTreeComponent.h"
#include "BehaviorTask.h"
#include "ActionTask.h"
#include "SequenceTask.h"
#include "EveryUpdateCalledAction.h"
#include "BehaviorTreeComponentTestBase.h"

using namespace DME;

class EmptyBehvaiorTask : public BehaviorTask
{
	TaskResult ProcessTask(float dt) override { return Success; };
};

TEST_GROUP_BASE(BehaviorTreeComponent,BehaviorTreeComponentTestBase)
{
};

TEST(BehaviorTreeComponent, IsEmptyOnCreation)
{
	CHECK_TRUE(component->IsEmpty());
}

TEST(BehaviorTreeComponent, IsNotEmptyAfterSettingRoot)
{
	auto task = new EmptyBehvaiorTask();
	component->SetRoot(task);

	CHECK_FALSE(component->IsEmpty());
}

TEST(BehaviorTreeComponent, RootIsExecutedOnUpdateIfItIsAnActionTask)
{
	unsigned callCount = 0u;
	auto task  = new ActionTask ([&](float dt)->TaskResult{ ++callCount; return Success; });
	component->SetRoot(task);

	CallMultipleUpdate(5);

	CHECK_EQUAL(5, callCount);
}
