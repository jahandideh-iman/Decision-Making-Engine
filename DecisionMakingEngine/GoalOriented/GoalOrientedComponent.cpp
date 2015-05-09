#include "GoalOrientedComponent.h"
#include "Core/DMEUtilities.h"


GoalOrientedComponent::GoalOrientedComponent()
{
}


GoalOrientedComponent::~GoalOrientedComponent()
{
	for (auto goal : goals)
		delete goal;
}

bool GoalOrientedComponent::HasNoGoal()
{
	return goals.empty();
}

void GoalOrientedComponent::Update(float dt)
{
	for (auto goal : goals)
		goal->Update(dt);
}

void GoalOrientedComponent::AddGoal(Goal *goal)
{
	goals.push_back(goal);
}
