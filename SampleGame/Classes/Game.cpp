#include "Game.h"


Door* Game::door = nullptr;
Key* Game::key = nullptr;
Room* Game::room = nullptr;

Game::Game()
{
}


Game::~Game()
{
}

cocos2d::Scene* Game::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Game::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Game::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	this->schedule(schedule_selector(Game::update));

	InititalBackground(visibleSize, origin);
	InitialPlayer(visibleSize, origin);
	InitialEnemies();

	InitialBehaviorTree();

	//NOTE: This must be after player initialization
	InitialKeyboardListener();

	return true;
}


void Game::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void Game::InitialKeyboardListener()
{
	auto eventListener = EventListenerKeyboard::create();


	eventListener->onKeyPressed= [&](EventKeyboard::KeyCode keyCode, Event* event){

		switch (keyCode){
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			player->SetXDir(-1);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			player->SetXDir(1);
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W:
			player->SetYDir(1);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
			player->SetYDir(-1);
			break;
		}
	};

	eventListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event){

		switch (keyCode){
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			player->SetXDir(0);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			player->SetXDir(0);
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W:
			player->SetYDir(0);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
			player->SetYDir(0);
			break;
		}
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, player);
}

void Game::InititalBackground(Size &visibleSize, Vec2 &origin)
{
	auto background = Sprite::create("Background.png");

	// position the sprite on the center of the screen
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	ScaleSpriteToDesignSize(background);
	// add the sprite as a child to this layer
	this->addChild(background, -100);

}

void Game::InitialPlayer(Size &visibleSize, Vec2 &origin)
{
	player = Player::CreatePlayer(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(player,50);
}

void Game::InitialEnemies()
{
	/*fsmEnemy = FSMEnemy::Create(Vec2( 0.2 * visibleSize.width , visibleSize.height / 2 + origin.y), player);
	this->addChild(fsmEnemy);

	daEnemey = DecisionTreeEnemey::Create(Vec2(0.8 * visibleSize.width, visibleSize.height / 2 + origin.y), player);
	this->addChild(daEnemey);
*/
	
}

void Game::update(float dt)
{
	DMEManager::Get()->Update(dt);
}

void Game::InitialBehaviorTree()
{
	BTAgent = BehaviorTreeAgent::Create(Vec2(0.8 * visibleSize.width, 0.55 * visibleSize.height / 2 + origin.y));
	this->addChild(BTAgent);

	door = Door::Create(Vec2(0.8 * visibleSize.width, 0.6 * visibleSize.height  + origin.y));
	this->addChild(door);

	key = new Key(Vec2(0.2 * visibleSize.width, 0.2 * visibleSize.height + origin.y));
	this->addChild(key);

	room = new Room(Vec2(0.8 * visibleSize.width, 0.8 * visibleSize.height + origin.y));
	this->addChild(room);

	door->isOpen = false;
	door->isUnlockable = true;
}



