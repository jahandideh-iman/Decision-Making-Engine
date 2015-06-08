#pragma once

#include <cocos2d.h>

using namespace cocos2d;


class Door : public CCSprite
{
public:
	static Door* Create(CCPoint pos);

	bool IsOpen();

	bool IsUnlockable();

	void Unlock();
	void Break();

public:

	bool isOpen = true;
	bool isUnlockable = true;
};

