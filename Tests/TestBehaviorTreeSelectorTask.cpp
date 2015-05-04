#include "CppUTest/TestHarness.h"
#include "BehaviorTreeComponent.h"
#include "SelectorTask.h"
#include "BehaviorTaskMockClasses.h"
#include "BehaviorTreeComponentTestBase.h"

TEST_GROUP_BASE(SelectorTask, BehaviorTreeComponentTestBase)
{

};

TEST(SelectorTask, ReturnsFailIfAllTasksFail)
{

	auto selectorTask = new SelectorTask();
	selectorTask->AddTask(new FailedMockTask());
	selectorTask->AddTask(new FailedMockTask());
	selectorTask->AddTask(new FailedMockTask());

	auto taskResult = selectorTask->ProcessTask(0.5);

	CHECK_EQUAL(TaskResult::Failure, taskResult);

	delete selectorTask;
}