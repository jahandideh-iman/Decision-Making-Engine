#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class Key :
	public CCSprite
{
public:
	Key(CCPoint pos);
	~Key();

	void PickUp();
};

