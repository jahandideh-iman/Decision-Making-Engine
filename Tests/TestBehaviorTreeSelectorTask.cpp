#include "CppUTest/TestHarness.h"
#include "BehaviorTreeComponent.h"
#include "SelectorTask.h"
#include "BehaviorTaskMockClasses.h"

TEST_GROUP(SelectorTask)
{

};

TEST(SelectorTask, ReturnsFailIfAllTasksFail)
{
	auto component = new BehaviorTreeComponent();

	auto selectorTask = new SelectorTask();
	selectorTask->AddTask(new FailedMockTask());
	selectorTask->AddTask(new FailedMockTask());
	selectorTask->AddTask(new FailedMockTask());

	auto taskResult = selectorTask->ProcessTask(0.5);

	CHECK_EQUAL(TaskResult::Failure, taskResult);

	delete component;
	delete selectorTask;
}