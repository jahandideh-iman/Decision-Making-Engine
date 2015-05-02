#include "CppUTest/TestHarness.h"
#include "BehaviorTreeComponent.h"
#include "SequenceTask.h"
#include "ActionTask.h"
#include <vector>

class MockTask : public BehaviorTask
{
public:
	bool isCalled = false;
	unsigned callCount = 0;

	virtual TaskResult ProcessTask(float dt) = 0;
};
class SuccessfulMockTask : public MockTask
{
public:
	TaskResult ProcessTask(float dt)
	{
		callCount++;
		isCalled = true;
		return TaskResult::Success;
	}

};

class FailedMockTask : public MockTask
{
public:
	TaskResult ProcessTask(float dt)
	{
		callCount++;
		isCalled = true;
		return TaskResult::Failure;
	}
};

class UnfinishedMockTask : public MockTask
{
public:
	TaskResult ProcessTask(float dt)
	{
		callCount++;
		isCalled = true;
		return TaskResult::Unfinished;
	}
};


TEST_GROUP(SequenceTask)
{
	BehaviorTreeComponent *component;
	SequenceTask *sequenceTask;

	std::vector<MockTask *> tasksVector;

	void setup()
	{
		component = new BehaviorTreeComponent();
		sequenceTask = new SequenceTask();

		component->SetRoot(sequenceTask);
	}

	void teardown()
	{
		delete component;
	}

	void AddTaskVectorToSequenceTask()
	{
		for (auto task : tasksVector)
			sequenceTask->AddTask(task);
	}

	void CallMultipleUpdate(unsigned numberOfTimes)
	{
		for (unsigned i = 0; i < numberOfTimes; ++i)
			component->Update(0.5);
	}

};

TEST(SequenceTask, ReturnSuccessIfAllTaskAreSuccessful)
{
	tasksVector.emplace_back(new SuccessfulMockTask());
	tasksVector.emplace_back(new SuccessfulMockTask());
	tasksVector.emplace_back(new SuccessfulMockTask());
	AddTaskVectorToSequenceTask();

	auto result = sequenceTask->ProcessTask(0.5);

	CHECK_EQUAL(result, TaskResult::Success);
}

TEST(SequenceTask, ReturnFailureIfOneChildIsFailed)
{
	tasksVector.emplace_back(new SuccessfulMockTask());
	tasksVector.emplace_back(new FailedMockTask());
	tasksVector.emplace_back(new SuccessfulMockTask());
	AddTaskVectorToSequenceTask();

	auto result = sequenceTask->ProcessTask(0.5);

	CHECK_EQUAL(result, TaskResult::Failure);
}

TEST(SequenceTask, ReturnUnfinishedIfOneChildIsNotFinished)
{
	tasksVector.emplace_back(new SuccessfulMockTask());
	tasksVector.emplace_back(new UnfinishedMockTask());
	tasksVector.emplace_back(new SuccessfulMockTask());
	AddTaskVectorToSequenceTask();

	auto result = sequenceTask->ProcessTask(0.5);

	CHECK_EQUAL(result, TaskResult::Unfinished);
}

TEST(SequenceTask, ChildrenAreCalledInSingleUpdateIfTheyAreSuccessful)
{
	tasksVector.emplace_back(new SuccessfulMockTask());
	tasksVector.emplace_back(new SuccessfulMockTask());
	tasksVector.emplace_back(new SuccessfulMockTask());
	AddTaskVectorToSequenceTask();

	component->Update();

	CHECK_TRUE(tasksVector[0]->isCalled);
	CHECK_TRUE(tasksVector[1]->isCalled);
	CHECK_TRUE(tasksVector[2]->isCalled);
}

TEST(SequenceTask, ChildernAfterAFaildTaskAreNotCalledInSignleUpdate)
{
	tasksVector.emplace_back(new SuccessfulMockTask());
	tasksVector.emplace_back(new FailedMockTask());
	tasksVector.emplace_back(new SuccessfulMockTask());
	AddTaskVectorToSequenceTask();

	component->Update();

	CHECK_TRUE(tasksVector[0]->isCalled);
	CHECK_TRUE(tasksVector[1]->isCalled);
	CHECK_FALSE(tasksVector[2]->isCalled);
}

TEST(SequenceTask, TasksAreCalledFromTheBeginingOnUpdateIfATaskIsFailed)
{
	tasksVector.emplace_back(new SuccessfulMockTask());
	tasksVector.emplace_back(new FailedMockTask());
	tasksVector.emplace_back(new SuccessfulMockTask());
	AddTaskVectorToSequenceTask();

	CallMultipleUpdate(5);

	CHECK_EQUAL(5,tasksVector[0]->callCount);
	CHECK_EQUAL(5, tasksVector[1]->callCount);
	CHECK_EQUAL(0, tasksVector[2]->callCount);
}

TEST(SequenceTask, ChildernAfterAnUnfinishedTaskAreNotCalledInSignleUpdate)
{
	tasksVector.emplace_back(new SuccessfulMockTask());
	tasksVector.emplace_back(new UnfinishedMockTask());
	tasksVector.emplace_back(new SuccessfulMockTask());
	AddTaskVectorToSequenceTask();

	component->Update();

	CHECK_TRUE(tasksVector[0]->isCalled);
	CHECK_TRUE(tasksVector[1]->isCalled);
	CHECK_FALSE(tasksVector[2]->isCalled);
}

TEST(SequenceTask, TasksAreCalledFromTheUnfinishedTaskOnUpdateIfATaskIsNotFinished)
{
	tasksVector.emplace_back(new SuccessfulMockTask());
	tasksVector.emplace_back(new UnfinishedMockTask());
	tasksVector.emplace_back(new SuccessfulMockTask());
	AddTaskVectorToSequenceTask();

	CallMultipleUpdate(5);

	//first task is called on first update
	CHECK_EQUAL(1, tasksVector[0]->callCount);
	CHECK_EQUAL(5, tasksVector[1]->callCount);
	CHECK_EQUAL(0, tasksVector[2]->callCount);
}
