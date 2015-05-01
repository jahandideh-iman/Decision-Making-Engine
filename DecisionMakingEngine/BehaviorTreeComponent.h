#pragma once
#include "DMEComponent.h"
#include "BehaviorTask.h"

class BehaviorTreeComponent :
	public DMEComponent
{
public:
	BehaviorTreeComponent();
	~BehaviorTreeComponent();

	void Update(float dt = 0) override;

	void SetRoot(BehaviorTask *task);
	bool IsEmpty();
private:
	BehaviorTask *root = nullptr;
};

