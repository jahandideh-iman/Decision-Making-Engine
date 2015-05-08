#pragma once
#include "DMEComponent.h"
#include "Goal.h"
#include <vector>

class GoalOrientedComponent :
	public DMEComponent
{
public:
	GoalOrientedComponent();
	~GoalOrientedComponent();

	bool HasNoGoal();

	void Update(float dt);

	void AddGoal(Goal *goal);

private:
	std::vector<Goal*> goals;
};

