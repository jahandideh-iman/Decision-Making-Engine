
#include "Door.h"


Door* Door::Create(CCPoint pos)
{
	Door *p = new Door;
	if (p && p->initWithFile("Door.png"))
	{
		p->autorelease();
		p->setPosition(pos);
		p->setAnchorPoint(CCPoint(0.5, 0.5));
		return p;
	}
	return nullptr;
}

bool Door::IsOpen()
{
	return isOpen;
}

bool Door::IsUnlockable()
{
	return isUnlockable;
}

void Door::Unlock()
{
	isOpen = true;
	setVisible(false);
}

void Door::Break()
{
	isOpen = true;
	setVisible(false);
}
