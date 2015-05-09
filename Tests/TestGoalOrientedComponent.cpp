#include "CppUTest/TestHarness.h"
#include "GoalOriented/GoalOrientedComponent.h"

TEST_GROUP(GoalOrientedComponent)
{
	GoalOrientedComponent component;

};

TEST(GoalOrientedComponent, HasNoGoalsOnCreation)
{
	CHECK_TRUE(component.HasNoGoal());
}

TEST(GoalOrientedComponent, IsNotEmptyAfterAddingGoal)
{
	auto goal = new Goal("Hunger");

	component.AddGoal(goal);

	CHECK_FALSE(component.HasNoGoal());
}

TEST(GoalOrientedComponent, GoalInsistenceChangesBasedOnRate)
{
	auto goal = new Goal("Hunger", 2, 5);

	component.AddGoal(goal);

	component.Update(1.00);

	CHECK_EQUAL(2 + 5,goal->GetInsistence());
}

//TEST(GoalOrientedComponent, ChooseActionForTheGoal)
//{
//	auto goal = new Goal("Hunger", 10);
//	auto gameObject = new GameObject();
//	gameObject->AddAction(new Action( , ))
//}