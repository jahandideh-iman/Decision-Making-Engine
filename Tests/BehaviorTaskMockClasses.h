#include "BehaviorTask.h"

class MockTask : public BehaviorTask
{
public:
	bool isCalled = false;
	unsigned callCount = 0;

	virtual TaskResult ProcessTask(float dt)
	{
		callCount++;
		isCalled = true;
		return TaskResult::None;
	}
};
class SuccessfulMockTask : public MockTask
{
public:
	TaskResult ProcessTask(float dt)
	{
		MockTask::ProcessTask(dt);
		return TaskResult::Success;
	}

};

class FailedMockTask : public MockTask
{
public:
	TaskResult ProcessTask(float dt)
	{
		MockTask::ProcessTask(dt);
		return TaskResult::Failure;
	}
};

class UnfinishedMockTask : public MockTask
{
public:
	TaskResult ProcessTask(float dt)
	{
		MockTask::ProcessTask(dt);
		return TaskResult::Unfinished;
	}
};