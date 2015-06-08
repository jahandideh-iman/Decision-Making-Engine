#include "BehaviorTreeAgent.h"

#include "Factories/InterfaceFactory.h"
#include "BehaviorTree/Task.h"
#include "Core/DMEManager.h"
#include "BehaviorTree/BehaviorTreeComponent.h";
#include "Core/DMEUtilities.h"

#include "Game.h"

using DME::InterfaceFactory;

#define SPEED 80

BehaviorTreeAgent::BehaviorTreeAgent()
{
}


BehaviorTreeAgent::~BehaviorTreeAgent()
{
}

BehaviorTreeAgent * BehaviorTreeAgent::Create(CCPoint initialPos)
{
	BehaviorTreeAgent* p = new BehaviorTreeAgent();
	if (p && p->initWithFile("BehaviorTreeAgent.png"))
	{
		p->autorelease();
		p->setPosition(initialPos);
		p->setAnchorPoint(CCPoint(0.5, 0.5));
		p->scheduleUpdate();
		p->InitialAIComponent();
		return p;
	}
	return nullptr;
}

void BehaviorTreeAgent::InitialAIComponent()
{
	auto * comp = dynamic_cast<BehaviorTreeComponent *> (DMEManager::Get()->CreateComponentFromFile("BehaviorTree.txt"));

	comp->SetTask("MoveToDoor", InterfaceFactory::CreateTask(BIND_MEMBER_UPDATE_ACTION(BehaviorTreeAgent::MoveToDoor, this)));
	comp->SetTask("IsDoorOpen", InterfaceFactory::CreateTask(BIND_MEMBER_UPDATE_ACTION(BehaviorTreeAgent::IsDoorOpen, this)));
	comp->SetTask("IsDoorUnlockable", InterfaceFactory::CreateTask(BIND_MEMBER_UPDATE_ACTION(BehaviorTreeAgent::IsDoorUnlockable, this)));
	comp->SetTask("GetTheKey", InterfaceFactory::CreateTask(BIND_MEMBER_UPDATE_ACTION(BehaviorTreeAgent::GetTheKey, this)));
	comp->SetTask("UnlockDoor", InterfaceFactory::CreateTask(BIND_MEMBER_UPDATE_ACTION(BehaviorTreeAgent::UnlockDoor, this)));
	comp->SetTask("BreakDoor", InterfaceFactory::CreateTask(BIND_MEMBER_UPDATE_ACTION(BehaviorTreeAgent::BreakDoor, this)));
	comp->SetTask("MoveToRoom", InterfaceFactory::CreateTask(BIND_MEMBER_UPDATE_ACTION(BehaviorTreeAgent::MoveToRoom, this)));
	comp->SetTask("Stop", InterfaceFactory::CreateTask(BIND_MEMBER_UPDATE_ACTION(BehaviorTreeAgent::Stop, this)));

	DMEManager::Get()->AddComponent(comp);
}

auto BehaviorTreeAgent::MoveToDoor(float dt) -> TaskResult
{
	if (this->getPosition().distance(Game::door->getPosition()) < SPEED * dt)
		return TaskResult::Success;

	CCPoint direction = Game::door->getPosition() - getPosition();
	direction.normalize();
	setPosition(getPosition() + direction * SPEED * dt);

	return TaskResult::Unfinished;
}

auto BehaviorTreeAgent::IsDoorOpen(float dt)->TaskResult
{
	if (Game::door->IsOpen())
		return TaskResult::Success;
	else
		return TaskResult::Failure;
}

auto BehaviorTreeAgent::IsDoorUnlockable(float dt) -> TaskResult
{
	if (Game::door->IsUnlockable())
		return TaskResult::Success;
	else
		return TaskResult::Failure;
}

auto BehaviorTreeAgent::GetTheKey(float dt) -> TaskResult
{
	if (this->getPosition().distance(Game::key->getPosition()) < SPEED * dt)
	{
		Game::key->PickUp();
		return TaskResult::Success;
	}


	CCPoint direction = Game::key->getPosition() - getPosition();
	direction.normalize();
	setPosition(getPosition() + direction * SPEED * dt);

	return TaskResult::Unfinished;
}

auto BehaviorTreeAgent::UnlockDoor(float dt)->TaskResult
{
	Game::door->Unlock();
	return TaskResult::Success;
}

auto BehaviorTreeAgent::BreakDoor(float dt)->TaskResult
{
	Game::door->setOpacity(Game::door->getOpacity() - 20 * dt);

	if (Game::door->getOpacity() <= 0)
	{
		Game::door->Break();
		return TaskResult::Success;
	}

	return TaskResult::Unfinished;

}

auto BehaviorTreeAgent::MoveToRoom(float dt) -> TaskResult
{
	if (this->getPosition().distance(Game::room->getPosition()) < SPEED * dt)
	{
		this->setPosition(Game::room->getPosition());
		return TaskResult::Success;
	}
		
	CCPoint direction = Game::room->getPosition() - getPosition();
	direction.normalize();
	setPosition(getPosition() + direction * SPEED * dt);

	return TaskResult::Unfinished;
}

auto BehaviorTreeAgent::Stop(float dt) -> TaskResult
{
	return TaskResult::Unfinished;
}
