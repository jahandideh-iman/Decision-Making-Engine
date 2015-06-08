#include "Key.h"


Key::Key(CCPoint pos)
{
	initWithFile("Key.png");

	autorelease();
	setPosition(pos);
	setAnchorPoint(CCPoint(0.5, 0.5));
}

Key::~Key()
{
}

void Key::PickUp()
{
	setVisible(false);
}
