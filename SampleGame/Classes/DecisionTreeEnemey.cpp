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
	DecisionTreeComponent * comp = new DecisionTreeComponent();

	ActionNode* playerInRangeAction = new ActionNode(BIND_MEMBER_UPDATE_ACTION(DecisionTreeEnemey::FollowPlayer, this));
	ActionNode* playerNotInRangeAction = new ActionNode(BIND_MEMBER_UPDATE_ACTION(DecisionTreeEnemey::SearchForPlayer, this));
	DecisionNode* InRangeQuery = new DecisionNode(BIND_MEMBER_ACTION(DecisionTreeEnemey::IsPlayerInRange, this), playerInRangeAction, playerNotInRangeAction);

	comp->SetRoot(InRangeQuery);

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
