#include "DecisionTreeEnemey.h"


DecisionTreeEnemey::DecisionTreeEnemey()
{
}


DecisionTreeEnemey::~DecisionTreeEnemey()
{
}

DecisionTreeEnemey* DecisionTreeEnemey::Create(CCPoint initialPos, Player* player)
{
	DecisionTreeEnemey* p = new DecisionTreeEnemey();
	if (p && p->initWithFile("Enemy_DecisionTree.png"))
	{
		p->autorelease();
		p->setPosition(initialPos);
		p->setAnchorPoint(CCPoint(0.5, 0.5));
		p->scheduleUpdate();
		p->Initial(player);
		return p;
	}
	return nullptr;
}

void DecisionTreeEnemey::Initial(Player* player)
{
	DecisionTreeComponent * comp = (DecisionTreeComponent*)DMEManager::Get()->CreateComponentFromFile("DTEnemy.txt");

	comp->SetActionMethod("FollowPlayer", new DME::EveryUpdateCalledAction(BIND_MEMBER_UPDATE_ACTION(DecisionTreeEnemey::FollowPlayer, this)));
	comp->SetActionMethod("SearchForPlayer", new DME::EveryUpdateCalledAction(BIND_MEMBER_UPDATE_ACTION(DecisionTreeEnemey::SearchForPlayer, this)));
	comp->SetConditionMethod("IsPlayerInRange", new DME::Condition(BIND_MEMBER_ACTION(DecisionTreeEnemey::IsPlayerInRange, this)));

	DMEManager::Get()->AddComponent(comp);
	this->player = player;
}

bool DecisionTreeEnemey::IsPlayerInRange()
{
	return getPosition().getDistance(player->getPosition()) < 200;
}

void DecisionTreeEnemey::SearchForPlayer(float dt)
{

}

void DecisionTreeEnemey::FollowPlayer(float dt)
{
	CCPoint direction = player->getPosition() - getPosition();
	direction.normalize();
	setPosition(getPosition() + direction * ENEMEY_SPEED * dt);
}
