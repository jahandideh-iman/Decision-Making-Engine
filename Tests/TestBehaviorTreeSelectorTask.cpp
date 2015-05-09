#include "CppUTest/TestHarness.h"
#include "BehaviorTree/SelectorTask.h"
#include "BehaviorTaskMockClasses.h"
#include "BehaviorTreeComponentTestBase.h"

TEST_GROUP_BASE(SelectorTask, BehaviorTreeComponentTestBase)
{
	SelectorTask * selectorTask;
	std::vector<MockTask *> tasksVector;

	void setup()
	{
		BehaviorTreeComponentTestBase::setup();
		selectorTask = new SelectorTask();

		component->SetRoot(selectorTask);
	}

	void AddTaskVectorToSelectorTask()
	{
		for (auto task : tasksVector)
			selectorTask->AddTask(task);
	}

};

TEST(SelectorTask, ReturnsFailIfAllTasksFail)
{
	selectorTask->AddTask(new FailedMockTask());
	selectorTask->AddTask(new FailedMockTask());
	selectorTask->AddTask(new FailedMockTask());

	auto taskResult = selectorTask->ProcessTask(0.5);

	CHECK_EQUAL(TaskResult::Failure, taskResult);
}

TEST(SelectorTask, ReturnsSuccessIfOneTaskSuccess)
{
	selectorTask->AddTask(new FailedMockTask());
	selectorTask->AddTask(new SuccessfulMockTask());
	selectorTask->AddTask(new FailedMockTask());

	auto taskResult = selectorTask->ProcessTask(0.5);

	CHECK_EQUAL(TaskResult::Success, taskResult);
}

TEST(SelectorTask, ReturnsUnfinishIfOneTaskUnfinish)
{
	selectorTask->AddTask(new FailedMockTask());
	selectorTask->AddTask(new UnfinishedMockTask());
	selectorTask->AddTask(new FailedMockTask());

	auto taskResult = selectorTask->ProcessTask(0.5);

	CHECK_EQUAL(TaskResult::Unfinished, taskResult);
}

TEST(SelectorTask, CallsChildrenInSingleUpdateIfTheyFail)
{
	tasksVector.emplace_back(new FailedMockTask());
	tasksVector.emplace_back(new FailedMockTask());
	tasksVector.emplace_back(new FailedMockTask());
	AddTaskVectorToSelectorTask();

	component->Update();

	CHECK_TRUE(tasksVector[0]->isCalled);
	CHECK_TRUE(tasksVector[1]->isCalled);
	CHECK_TRUE(tasksVector[2]->isCalled);
}

TEST(SelectorTask, DoesNotCallTheChildrenAfterASuccessfulTaskOnSingleUpdate)
{
	tasksVector.emplace_back(new FailedMockTask());
	tasksVector.emplace_back(new SuccessfulMockTask());
	tasksVector.emplace_back(new MockTask());
	AddTaskVectorToSelectorTask();

	component->Update();

	CHECK_TRUE(tasksVector[0]->isCalled);
	CHECK_TRUE(tasksVector[1]->isCalled);
	CHECK_FALSE(tasksVector[2]->isCalled);
}

TEST(SelectorTask, DoesNotCallTheChildrenAfterAnUnfinishedTaskOnSingleUpdate)
{
	tasksVector.emplace_back(new FailedMockTask());
	tasksVector.emplace_back(new UnfinishedMockTask());
	tasksVector.emplace_back(new MockTask());
	AddTaskVectorToSelectorTask();

	component->Update();

	CHECK_TRUE(tasksVector[0]->isCalled);
	CHECK_TRUE(tasksVector[1]->isCalled);
	CHECK_FALSE(tasksVector[2]->isCalled);
}

TEST(SelectorTask, CallsChildrenFromTheBeginingIfOnNextUpdateIfOneTaskIsSuccessful)
{
	tasksVector.emplace_back(new FailedMockTask());
	tasksVector.emplace_back(new SuccessfulMockTask());
	tasksVector.emplace_back(new MockTask());
	AddTaskVectorToSelectorTask();

	CallMultipleUpdate(5);

	CHECK_EQUAL(5, tasksVector[0]->callCount);
	CHECK_EQUAL(5, tasksVector[1]->callCount);
	CHECK_EQUAL(0, tasksVector[2]->callCount);
}

TEST(SelectorTask, StartsFromTheUnfinishedTaskOnNextUpdate)
{
	tasksVector.emplace_back(new FailedMockTask());
	tasksVector.emplace_back(new UnfinishedMockTask());
	tasksVector.emplace_back(new MockTask());
	AddTaskVectorToSelectorTask();

	CallMultipleUpdate(5);

	//first task is called on first update
	CHECK_EQUAL(1, tasksVector[0]->callCount);
	CHECK_EQUAL(5, tasksVector[1]->callCount);
	CHECK_EQUAL(0, tasksVector[2]->callCount);
}