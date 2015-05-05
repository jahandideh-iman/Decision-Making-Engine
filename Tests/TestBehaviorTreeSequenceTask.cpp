#include "CppUTest/TestHarness.h"
#include "BehaviorTreeComponent.h"
#include "SequenceTask.h"
#include "BehaviorTaskMockClasses.h"
#include "BehaviorTreeComponentTestBase.h"
#include <vector>


TEST_GROUP_BASE(SequenceTask,BehaviorTreeComponentTestBase) 
{
	SequenceTask *sequenceTask;

	std::vector<MockTask *> tasksVector;

	void setup() override
	{
		BehaviorTreeComponentTestBase::setup();
		sequenceTask = new SequenceTask();

		component->SetRoot(sequenceTask);
	}

	void AddTaskVectorToSequenceTask()
	{
		for (auto task : tasksVector)
			sequenceTask->AddTask(task);
	}

};

TEST(SequenceTask, ReturnsSuccessIfAllTaskAreSuccessful)
{
	tasksVector.emplace_back(new SuccessfulMockTask());
	tasksVector.emplace_back(new SuccessfulMockTask());
	tasksVector.emplace_back(new SuccessfulMockTask());
	AddTaskVectorToSequenceTask();

	auto result = sequenceTask->ProcessTask(0.5);

	CHECK_EQUAL(result, TaskResult::Success);
}

TEST(SequenceTask, ReturnsFailureIfOneChildIsFailed)
{
	tasksVector.emplace_back(new SuccessfulMockTask());
	tasksVector.emplace_back(new FailedMockTask());
	tasksVector.emplace_back(new SuccessfulMockTask());
	AddTaskVectorToSequenceTask();

	auto result = sequenceTask->ProcessTask(0.5);

	CHECK_EQUAL(result, TaskResult::Failure);
}

TEST(SequenceTask, ReturnsUnfinishedIfOneChildIsNotFinished)
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
