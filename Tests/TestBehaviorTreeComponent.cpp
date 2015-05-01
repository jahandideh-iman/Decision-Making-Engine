#include "CppUTest/TestHarness.h"
#include "BehaviorTreeComponent.h"
#include "BehaviorTask.h"
#include "ActionTask.h"
#include "SequenceTask.h"
#include "EveryUpdateCalledAction.h"

using namespace DME;

class EmptyBehvaiorTask : public BehaviorTask
{
	void ProcessTask(float dt) override {};
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
	auto task  = new ActionTask ([&](float dt)->bool{ ++callCount; return true; });
	component->SetRoot(task);

	CallMultipleUpdate(5);

	CHECK_EQUAL(5, callCount);
}

TEST(BehaviorTreeComponent, SequenceTaskExecutedAllItsChildrenIfTheyAreAllSuccessful)
{
	unsigned callCount = 0u;
	auto action = [&](float dt)->bool{ ++callCount; return true; };

	auto sequenceTask = new SequenceTask();
	sequenceTask->AddTask(new ActionTask(action));
	sequenceTask->AddTask(new ActionTask(action));
	sequenceTask->AddTask(new ActionTask(action));

	component->SetRoot(sequenceTask);

	component->Update();

	CHECK_EQUAL(3, callCount);
}