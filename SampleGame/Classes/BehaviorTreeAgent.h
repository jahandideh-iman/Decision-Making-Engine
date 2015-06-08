#pragma once
#include "cocos2d.h"
#include "BehaviorTree/Task.h"

using namespace cocos2d;

class BehaviorTreeAgent : public CCSprite
{
	typedef Task::TaskResult TaskResult;
public:

	static BehaviorTreeAgent *Create(CCPoint initialPos);

	BehaviorTreeAgent();
	~BehaviorTreeAgent();

	TaskResult MoveToDoor(float dt);
	TaskResult IsDoorOpen(float dt);
	TaskResult IsDoorUnlockable(float dt);
	TaskResult GetTheKey(float dt);
	TaskResult UnlockDoor(float dt);
	TaskResult BreakDoor(float dt);
	TaskResult MoveToRoom(float dt);
	TaskResult Stop(float dt);

private:
	void InitialAIComponent();


};

