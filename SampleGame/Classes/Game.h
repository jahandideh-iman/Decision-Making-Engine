#pragma once

#include "cocos2d.h"
#include "Player.h"

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

	void InitialPlayer(Size &visibleSize, Vec2 &origin);

	void InititalBackground(Size &visibleSize, Vec2 &origin);

	void InitialKeyboardListener();


	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Game);

	static cocos2d::Scene* createScene();
private:
	Player * player = nullptr;
};

