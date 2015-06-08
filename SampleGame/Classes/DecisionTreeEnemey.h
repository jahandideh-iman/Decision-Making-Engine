#pragma once

#include "cocos2d.h"
#include "Player.h"
#include "DecisionTree/DecisionTreeComponent.h"
#include "Core/DMEUtilities.h"
#include "Core/DMEManager.h"

using namespace cocos2d;

#define ENEMEY_SPEED 60

class DecisionTreeEnemey : public CCSprite
{
public:

	static DecisionTreeEnemey* Create(CCPoint initialPos, Player* player);
	DecisionTreeEnemey();
	~DecisionTreeEnemey();

	bool IsPlayerInRange();
	void SearchForPlayer(float dt);
	void FollowPlayer(float dt);

private:
	void Initial(Player* player);

private:
	Player* player = nullptr;
};

