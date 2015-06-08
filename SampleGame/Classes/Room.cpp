#include "Room.h"


Room::Room(CCPoint pos)
{
	initWithFile("Room.png");

	autorelease();
	setPosition(pos);
	setAnchorPoint(CCPoint(0.5, 0.5));
}


Room::~Room()
{
}
