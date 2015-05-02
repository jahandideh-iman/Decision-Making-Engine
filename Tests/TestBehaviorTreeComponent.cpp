#include "CppUTest/TestHarness.h"
#include "BehaviorTreeComponent.h"
#include "BehaviorTask.h"
#include "ActionTask.h"
#include "SequenceTask.h"
#include "EveryUpdateCalledAction.h"

using namespace DME;

class EmptyBehvaiorTask : public BehaviorTask
{
	TaskResult ProcessTask(float dt) override { return Success; };
};

TEST_GROUP(BehaviorTreeComponent)
{
	BehaviorTreeComponent *component;
	void setup()
	{
		component = new BehaviorTreeComponent();
	}

	void teardown()
	{
		delete component;
	}

	void CallMultipleUpdate(unsigned numberOfTimes)
	{
		for (unsigned i = 0; i < numberOfTimes; ++i)
			component->Update(0.5);
	}

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
