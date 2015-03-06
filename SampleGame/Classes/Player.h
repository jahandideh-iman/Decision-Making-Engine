#pragma once

#include "cocos2d.h"


using namespace cocos2d;

#define SPEED 80

class Player : public CCSprite
{
public:

	static Player* CreatePlayer(CCPoint initialPos);
	Player();
	~Player();

	void SetXDir(int dir);
	void SetYDir(int dir);

	void update(float dt);
private:
	int xDir = 0;
	int yDir = 0;
};

