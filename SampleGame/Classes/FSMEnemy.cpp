#include "FSMEnemy.h"
#include <iostream>


FSMEnemy::FSMEnemy()
{
}


FSMEnemy::~FSMEnemy()
{
}

FSMEnemy* FSMEnemy::Create(CCPoint initialPos, Player* player)
{
	FSMEnemy* p = new FSMEnemy();
	if (p && p->initWithFile("Enemy_FSM.png"))
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

void FSMEnemy::Initial(Player* player)
{

	FiniteStateMachineComponent* comp = new FiniteStateMachineComponent();
	comp->AddState("Searching");
	comp->AddState("Following");
	comp->SetInitialState("Searching");
	comp->AddUpdateAction("SearchForPlayer");
	comp->AddUpdateAction("FollowPlayer");

	comp->SetUpdateActionMethod("SearchForPlayer", BIND_MEMBER_UPDATE_ACTION(FSMEnemy::SearchForPlayer, this));
	comp->SetUpdateActionMethod("FollowPlayer", BIND_MEMBER_UPDATE_ACTION(FSMEnemy::FollowPlayer, this));
		
	comp->SetTransition("Searching", "Following", BIND_MEMBER_ACTION(FSMEnemy::IsPlayerInRange, this));
	comp->SetTransition("Following", "Searching", BIND_MEMBER_ACTION(FSMEnemy::IsPlayerOutOfRange, this));
	comp->SetStateUpdateAction("Searching", "SearchForPlayer");
	comp->SetStateUpdateAction("Following", "FollowPlayer");

	DMEManager::Get()->AddComponent(comp);

	this->player = player;
}

bool FSMEnemy::IsPlayerInRange()
{
	return getPosition().getDistance(player->getPosition()) < 200;
}

bool FSMEnemy::IsPlayerOutOfRange()
{
	return getPosition().getDistance(player->getPosition()) > 250;
}

void FSMEnemy::SearchForPlayer(float dt)
{
	
}

void FSMEnemy::FollowPlayer(float dt)
{
	CCPoint direction = player->getPosition() - getPosition();
	direction.normalize();
	setPosition(getPosition() + direction * ENEMEY_SPEED * dt);
}
