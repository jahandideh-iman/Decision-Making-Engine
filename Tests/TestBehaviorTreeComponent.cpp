#include "BehaviorTreeComponentTestBase.h"
#include "BehaviorTaskMockClasses.h"


TEST_GROUP_BASE(BehaviorTreeComponent,BehaviorTreeComponentTestBase)
{
};

TEST(BehaviorTreeComponent, IsEmptyOnCreation)
{
	CHECK_TRUE(component->IsEmpty());
}

TEST(BehaviorTreeComponent, IsNotEmptyAfterSettingRoot)
{
	component->SetRoot(new MockTask());

	CHECK_FALSE(component->IsEmpty());
}

TEST(BehaviorTreeComponent, RootIsExecutedOnUpdate)
{
	auto task = new MockTask();
	component->SetRoot(task);

	CallMultipleUpdate(5);

	CHECK_EQUAL(5, task->callCount);
}
