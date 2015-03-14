#pragma once

#include "cocos2d.h"
#include "Player.h"
#include "DMEManager.h"
#include "FSMEnemy.h"
#include "DecisionTreeEnemey.h"

using namespace cocos2d;

static void ScaleSpriteToDesignSize(CCSprite* sprite)
{
	CCSize designSize = CCDirector::sharedDirector()->getOpenGLView()->getDesignResolutionSize();
	sprite->setScaleX(designSize.width / sprite->getContentSize().width);
	sprite->setScaleY(designSize.height / sprite->getContentSize().height);
}

class Game: public cocos2d::Layer
{
public:
	Game();
	~Game();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);

	void update(float dt) override;

	CREATE_FUNC(Game);

	static cocos2d::Scene* createScene();

private:
	void InitialPlayer(Size &visibleSize, Vec2 &origin);
	void InitialEnemies(Size &visibleSize, Vec2 &origin);

	void InititalBackground(Size &visibleSize, Vec2 &origin);
	void InitialKeyboardListener();

private:
	Player* player = nullptr;
	FSMEnemy* fsmEnemy = nullptr;
	DecisionTreeEnemey* daEnemey = nullptr;
};

