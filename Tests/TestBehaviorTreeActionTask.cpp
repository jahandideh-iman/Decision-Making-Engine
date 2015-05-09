#include "BehaviorTreeComponentTestBase.h"
#include "BehaviorTree/ActionTask.h"

TEST_GROUP_BASE(ActionTask, BehaviorTreeComponentTestBase)
{
};

TEST(ActionTask, IsCallOnUpdate)
{
	unsigned callCount = 0u;
	auto task = new ActionTask(component,"ActionName");
	component->AddAction("ActionName");
	component->SetActionMethod("ActionName", new TaskMethod([&](float dt)->TaskResult{++callCount; return TaskResult::Success; }));

	component->SetRoot(task);

	CallMultipleUpdate(5);

	CHECK_EQUAL(5, callCount);
}