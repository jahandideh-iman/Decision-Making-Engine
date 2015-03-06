#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

Player* Player::CreatePlayer(CCPoint initialPos)
{
	Player* p = new Player();
	if (p && p->initWithFile("Player.png"))
	{
		p->autorelease();
		p->setPosition(initialPos);
		p->setAnchorPoint(CCPoint(0.5, 0.5));
		p->scheduleUpdate();
		return p;
	}
	return nullptr;
}

void Player::SetXDir(int dir)
{
	xDir = dir;
}

void Player::SetYDir(int dir)
{
	yDir = dir;
}

void Player::update(float dt)
{
	auto xPos = getPosition().x;
	auto newXPos = xPos + xDir * SPEED * dt;
	setPositionX(newXPos);

	auto yPos = getPosition().y;
	auto newYPos = yPos + yDir * SPEED * dt;
	setPositionY(newYPos);
}


