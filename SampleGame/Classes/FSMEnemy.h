#pragma once

#include "cocos2d.h"
#include "FiniteStateMachine/FiniteStateMachineComponent.h"
#include "Core/DMEUtilities.h"
#include "Core/DMEManager.h"
#include "Player.h"

using namespace cocos2d;

#define ENEMEY_SPEED 60


class FSMEnemy : public CCSprite
{
public:

	static FSMEnemy* Create(CCPoint initialPos, Player* player);

	FSMEnemy();
	~FSMEnemy();

	bool IsPlayerInRange();
	bool IsPlayerOutOfRange();
	void SearchForPlayer(float dt);
	void FollowPlayer(float dt);

private:
	void Initial(Player* player);

private:
	Player* player = nullptr;
};

