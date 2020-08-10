#include "PlayScene4.h"
#include "SnareNote.h"
#include "PlayScene4.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "NormalNote.h"
#include "KickNote.h"
#include "time.h"
#include "SongEnding.h"
#include "Singleton_data.h"
#include "SimpleAudioEngine.h"
#include "Singleton_sounds.h"


using namespace CocosDenshion;

USING_NS_CC;

Scene* PlayScene4::createScene()
{
	return PlayScene4::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool PlayScene4::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(PlayScene4::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	back = Sprite::create("space.jpg");
	back->setAnchorPoint(Vec2(0, 0));
	back->setPosition(0, 0);
	backV.x = 0;
	backV.y = 0;
	this->addChild(back, 0);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("CITY", "fonts/bemin.ttf", 25);
	label->setColor(Color3B::ORANGE);
	if (label == nullptr)
	{
		problemLoading("'fonts/bemin.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(350, 750));

		// add the label as a child to this layer
		this->addChild(label, 1);
	}

	Singleton_data::getInstance()->Life = 1;
	Singleton_data::getInstance()->Score = 0;
	Singleton_data::getInstance()->Time = 0;
	Singleton_data::getInstance()->Stage = 4;

	SimpleAudioEngine::getInstance()->stopBackgroundMusic();




	auto tKeyListener = EventListenerKeyboard::create();
	tKeyListener->onKeyPressed = CC_CALLBACK_2(PlayScene4::onKeyPressed, this);
	tKeyListener->onKeyReleased = CC_CALLBACK_2(PlayScene4::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tKeyListener, this);



	mpListener = EventListenerTouchOneByOne::create();
	mpListener->setSwallowTouches(true);
	mpListener->onTouchBegan = CC_CALLBACK_2(PlayScene4::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mpListener, this);


	multiListener = EventListenerTouchAllAtOnce::create();
	multiListener->onTouchesBegan = CC_CALLBACK_2(PlayScene4::onTouchesBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(multiListener, this);






	mpSpriteA = Sprite::create("left.png");
	mpSpriteA->setPosition(Vec2(120, 250));
	mpSpriteA->setScale(0.2);
	mpSpriteA->retain();
	this->addChild(mpSpriteA, 5);

	auto leftAnimation = Animation::create();
	leftAnimation->setDelayPerUnit(0.1f);

	leftAnimation->addSpriteFrameWithFile("left.png");
	leftAnimation->addSpriteFrameWithFile("left2.png");
	leftAnimation->addSpriteFrameWithFile("left3.png");
	leftAnimation->addSpriteFrameWithFile("left4.png");
	leftAnimation->addSpriteFrameWithFile("left5.png");
	leftAnimation->addSpriteFrameWithFile("left6.png");
	leftAnimation->addSpriteFrameWithFile("left7.png");
	leftAnimation->addSpriteFrameWithFile("left8.png");

	auto leftAnimate = Animate::create(leftAnimation);
	auto leftRepeatForever = RepeatForever::create(leftAnimate);

	mpSpriteA->runAction(leftRepeatForever);


	mpSpriteB = Sprite::create("right.png");
	mpSpriteB->setPosition(Vec2(360, 250));
	mpSpriteB->setScale(0.2);
	mpSpriteB->retain();
	this->addChild(mpSpriteB, 5);

	auto rightAnimation = Animation::create();
	rightAnimation->setDelayPerUnit(0.1f);

	rightAnimation->addSpriteFrameWithFile("right.png");
	rightAnimation->addSpriteFrameWithFile("right2.png");
	rightAnimation->addSpriteFrameWithFile("right3.png");
	rightAnimation->addSpriteFrameWithFile("right4.png");
	rightAnimation->addSpriteFrameWithFile("right5.png");
	rightAnimation->addSpriteFrameWithFile("right6.png");
	rightAnimation->addSpriteFrameWithFile("right7.png");
	rightAnimation->addSpriteFrameWithFile("right8.png");

	auto rightAnimate = Animate::create(rightAnimation);
	auto rightRepeatForever = RepeatForever::create(rightAnimate);

	mpSpriteB->runAction(rightRepeatForever);


	mpSpriteC = Sprite::create("space.png");
	mpSpriteC->setPosition(Vec2(240, 150));
	this->addChild(mpSpriteC, 5);
	mpSpriteC->setScale(0.15);
	mpSpriteC->retain();

	auto spaceAnimation = Animation::create();
	spaceAnimation->setDelayPerUnit(0.1f);

	spaceAnimation->addSpriteFrameWithFile("space.png");
	spaceAnimation->addSpriteFrameWithFile("space2.png");
	spaceAnimation->addSpriteFrameWithFile("space3.png");
	spaceAnimation->addSpriteFrameWithFile("space4.png");
	spaceAnimation->addSpriteFrameWithFile("space5.png");
	spaceAnimation->addSpriteFrameWithFile("space6.png");
	spaceAnimation->addSpriteFrameWithFile("space7.png");
	spaceAnimation->addSpriteFrameWithFile("space8.png");

	auto spaceAnimate = Animate::create(spaceAnimation);
	auto spaceRepeatForever = RepeatForever::create(spaceAnimate);

	mpSpriteC->runAction(spaceRepeatForever);



	barspr = Sprite::create("bar.png");
	barspr->setAnchorPoint(Point(1, 0.5));
	barv.y = 785;
	barv.x = 0;
	barspr->setPosition(barv);
	this->addChild(barspr, 5);

	barspr2 = Sprite::create("bar2.png");
	barspr2->setAnchorPoint(Point(0, 0.5));
	barspr2->setPosition(Vec2(0, 785));
	this->addChild(barspr2, 4);

	if (Singleton_sounds::getInstance()->MS == 0)
	{
		bar_count = 480 / 234;
	}
	else if (Singleton_sounds::getInstance()->MS == 1)
	{
		bar_count = 480.0f / 182.0f;
	}
	else if (Singleton_sounds::getInstance()->MS == 2)
	{
		bar_count = 480 / 234;
	}


	srand((unsigned int)time(nullptr));
	for (int ti = 0; ti < 4; ti++)
	{
		int x = ti % 2;
		normalnote[ti] = new NormalNote();
		normalnote[ti]->create(this, x);
		this->addChild(normalnote[ti], 10);
	}
	for (int ti = 0; ti < 3; ti++)
	{
		kicknote[ti] = new KickNote();
		kicknote[ti]->create(this);
		this->addChild(kicknote[ti], 10);
	}
	snarenote = new SnareNote();
	snarenote->create(this);
	this->addChild(snarenote, 10);


	this->schedule(schedule_selector(PlayScene4::OnTimer), 0.22222222);
	this->schedule(schedule_selector(PlayScene4::kicktimer), 0.22222222);
	this->scheduleOnce(schedule_selector(PlayScene4::snaretimer), 1.77777776);
	this->schedule(schedule_selector(PlayScene4::bartimer), 0.5);
	this->scheduleUpdate();

	return true;
}


void PlayScene4::bartimer(float t)
{


	barv.x = barv.x + bar_count;
	barspr->setPosition(barv);


}

void PlayScene4::update(float dt)
{


	


	for (int ti = 0; ti < 4; ti++)
	{
		if (nullptr != normalnote[ti])
		{
			normalnote[ti]->Update(dt);
		}
	}

	for (int ti = 0; ti < 3; ti++)
	{
		kicknote[ti]->Update(dt);
	}


	snarenote->Update(dt);


	backV.x = backV.x - 0.25;
	
	back->setPosition(backV);



	if (Singleton_data::getInstance()->Life <= 0)
	{
		die_ending();
	}


	if (barv.x >= 480)
	{
		die_ending();
	}



}

void PlayScene4::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		for (int ti = 0; ti < 4; ti++)
		{
			if (nullptr != normalnote[ti])
			{
				normalnote[ti]->left_check();
			}
		}

	}
	else if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{

		for (int ti = 0; ti < 4; ti++)
		{
			if (nullptr != normalnote[ti])
			{
				normalnote[ti]->right_check();
			}
		}
	}
	if (keycode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		for (int ti = 0; ti < 3; ti++)
		{
			kicknote[ti]->mid_check();
		}
		snarenote->mid_check();
	}

}



bool PlayScene4::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	auto tTouchPos = touch->getLocation();

	if (tTouchPos.x < 160)
	{
		for (int ti = 0; ti < 4; ti++)
		{
			if (nullptr != normalnote[ti])
			{
				normalnote[ti]->left_check();
			}
		}
	}
	else if (tTouchPos.x > 320)
	{
		for (int ti = 0; ti < 4; ti++)
		{
			if (nullptr != normalnote[ti])
			{
				normalnote[ti]->right_check();
			}
		}
	}
	else
	{
		for (int ti = 0; ti < 3; ti++)
		{
			kicknote[ti]->mid_check();
		}
		snarenote->mid_check();
	}


	return true;
}


void PlayScene4::onTouchesBegan(const std::vector<Touch*>& touches, Event* event)
{
	for (int ti = 0; ti < 3; ti++)
	{
		auto touch = touches[0];
		auto touchPoint = touch->getLocation();

		if (touchPoint.x < 160)
		{
			for (int ti = 0; ti < 4; ti++)
			{
				if (nullptr != normalnote[ti])
				{
					normalnote[ti]->left_check();
				}
			}
		}
		else if (touchPoint.x > 320)
		{
			for (int ti = 0; ti < 4; ti++)
			{
				if (nullptr != normalnote[ti])
				{
					normalnote[ti]->right_check();
				}
			}
		}
		else
		{
			for (int j = 0; j < 3; ti++)
			{
				kicknote[ti]->mid_check();
			}
			snarenote->mid_check();
		}



	}
}






void PlayScene4::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{



	}
	else if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{



	}
}

void PlayScene4::kicktimer(float t)
{
	kick_count++;
	if (kick_count == 4)
	{
		kicknote[0]->DoAlive();
		Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->KS);
	
	}
	if (kick_count == 7)
	{
		kicknote[1]->DoAlive();
		Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->KS);
	}
	if (kick_count == 11)
	{
		kicknote[2]->DoAlive();
		Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->KS);
	}
}

void PlayScene4::snaretimer(float t)
{
	snarenote->DoAlive();
	Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->SS);

}


void PlayScene4::OnTimer(float  f)
{

	normal_count++;

	if (normal_count == 4)
	{
		normalnote[0]->DoAlive();
		Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->HS);
	}
	if (normal_count == 6)
	{
		normalnote[1]->DoAlive();
		Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->HS);
	}
	if (normal_count == 8)
	{
		normalnote[2]->DoAlive();
		Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->HS);
	}
	if (normal_count == 10)
	{
		normalnote[3]->DoAlive();
		Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->HS);
	}


}

void PlayScene4::die_ending()
{
	Singleton_data::getInstance()->savepercent(barv.x);
	auto pScene = SongEnding::createScene();

	Director::getInstance()->replaceScene(pScene);
}


void PlayScene4::update_stat(float dt)
{
	char tempz[512];
	memset(tempz, 0, 512);
	sprintf(tempz, "Time: %3.2f", Singleton_data::getInstance()->Time);

	std::string tString = tempz;

	Time->setString(tString);

	char tempz2[512];
	memset(tempz2, 0, 512);
	sprintf(tempz2, "Score: %d", Singleton_data::getInstance()->Score);

	std::string tString2 = tempz2;

	Score->setString(tString2);
}



void PlayScene4::menuCloseCallback(Ref* pSender)
{
	/*this->schedule(schedule_selector(PlayScene4::OnTimer), 1);
	normal_count = 0;*/



	this->unscheduleUpdate();
	this->unschedule(schedule_selector(PlayScene4::OnTimer));

	////Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	EventCustom customEndEvent("game_scene_close_event");
	_eventDispatcher->dispatchEvent(&customEndEvent);


}
