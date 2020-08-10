#include "PlayScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "NormalNote.h"
#include "KickNote.h"
#include "time.h"
#include "EndScene.h"
#include "Singleton_data.h"
#include "Singleton_sounds.h"
#include "SnareNote.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
using namespace CocosDenshion;

Scene* PlayScene::createScene()
{
	return PlayScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool PlayScene::init()
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
		CC_CALLBACK_1(PlayScene::menuCloseCallback, this));

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
	auto menu = Menu::create( NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	Sprite* back = nullptr;
	back = Sprite::create("wall2.jpg");
	back->setAnchorPoint(Vec2(0, 0));
	back->setPosition(0, 0);
	this->addChild(back, 0);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("4Beats\nPractice", "fonts/bemin.ttf", 20);
	 
	if (label == nullptr)
	{
		problemLoading("'fonts/bemin.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(350,750));

		// add the label as a child to this layer
		this->addChild(label, 1);
	}

	Singleton_data::getInstance()->Life = 6;
	Singleton_data::getInstance()->Score = 0;
	Singleton_data::getInstance()->Time = 0;
	Singleton_data::getInstance()->Stage = 1;

	SimpleAudioEngine::getInstance()->stopBackgroundMusic();


	Time = Label::createWithTTF("Time:", "fonts/bemin.ttf", 25);

	Time->setAnchorPoint(Vec2(0, 0));
	Time->setPosition(Vec2(50, 750));
	this->addChild(Time, 1);

	Score = Label::createWithTTF("Score:", "fonts/bemin.ttf",25);

	Score->setAnchorPoint(Vec2(0, 0));
	Score->setPosition(Vec2(50, 720));
	this->addChild(Score, 1);


	auto tKeyListener = EventListenerKeyboard::create();
	tKeyListener->onKeyPressed = CC_CALLBACK_2(PlayScene::onKeyPressed, this);
	tKeyListener->onKeyReleased = CC_CALLBACK_2(PlayScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tKeyListener, this);


	mpListener = EventListenerTouchOneByOne::create();
	mpListener->setSwallowTouches(true);
	mpListener->onTouchBegan = CC_CALLBACK_2(PlayScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mpListener, this);

	multiListener = EventListenerTouchAllAtOnce::create();
	multiListener->onTouchesBegan = CC_CALLBACK_2(PlayScene::onTouchesBegan, this);
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


	for (int ti = 0; ti < 4; ti++)
	{
		int x = ti % 2;
		normalnote[ti] = new NormalNote();
		normalnote[ti]->create(this,x);
		this->addChild(normalnote[ti], 10);
	}

	kicknote = new KickNote();
	kicknote->create(this);
	this->addChild(kicknote, 10);


	snarenote = new SnareNote();
	snarenote->create(this);
	this->addChild(snarenote, 10);
	
	this->schedule(schedule_selector(PlayScene::OnTimer),0.44444444);
	this->scheduleOnce(schedule_selector(PlayScene::kicktimer), 0.88888888);
	this->scheduleOnce(schedule_selector(PlayScene::snaretimer), 1.77777776);
	this->scheduleUpdate();



	return true;
}

void PlayScene::update(float dt)
{
	update_stat(dt);

	Singleton_data::getInstance()->Time = Singleton_data::getInstance()->Time + dt;


	for (int ti = 0; ti < 4; ti++)
	{
		if (nullptr != normalnote[ti])
		{
			normalnote[ti]->Update(dt);
		}
	}



	kicknote->Update(dt);
	
	snarenote->Update(dt);





	if (Singleton_data::getInstance()->Life <= 0)
	{
		die_ending();
	}


	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying() == false && normal_count > 50)
	{
		Singleton_sounds::getInstance()->PlayBGM();
	}


}


void PlayScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
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
		kicknote->mid_check();

		snarenote->mid_check();
	}

}

void PlayScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{

		

	}
	else if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{

	

	}
}




bool PlayScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
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
		kicknote->mid_check();

		snarenote->mid_check();
	}


	return true;
}


void PlayScene::onTouchesBegan(const std::vector<Touch*>& touches, Event* event)
{
	for (int ti = 0; ti < 3; ti++)
	{
		auto touch = touches[0];
		auto touchPoint = touch->getLocation();
	
		if (touchPoint.x < 160 )
		{
			for (int ti = 0; ti < 4; ti++)
			{
				if (nullptr != normalnote[ti])
				{
					normalnote[ti]->left_check();
				}
			}
		}
		else if (touchPoint.x  > 320 )
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
			kicknote->mid_check();

			snarenote->mid_check();
		}



	}
}

void PlayScene::kicktimer(float t)
{
	kicknote->DoAlive();
	Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->KS);
}

void PlayScene::snaretimer(float t)
{
	snarenote->DoAlive();
	Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->SS);
}


void PlayScene::OnTimer(float  f)
{

	normal_count++;
	
	if (normal_count == 2) 
	{ 
		normalnote[0]->DoAlive();
		Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->HS);
	}
	if (normal_count == 3)
	{ 
		normalnote[1]->DoAlive();
		Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->HS);
	}
	if (normal_count == 4)
	{ 
		normalnote[2]->DoAlive();
		Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->HS);
	}
	if (normal_count == 5)
	{ 
		normalnote[3]->DoAlive();
		Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->HS);
	}

	
}

void PlayScene::die_ending()
{
	auto pScene = EndScene::createScene();

	Director::getInstance()->replaceScene(pScene);
}


void PlayScene::update_stat(float dt)
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



void PlayScene::menuCloseCallback(Ref* pSender)
{
	/*this->schedule(schedule_selector(PlayScene::OnTimer), 1);
	normal_count = 0;*/



	this->unscheduleUpdate();
	this->unschedule(schedule_selector(PlayScene::OnTimer));

	////Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	EventCustom customEndEvent("game_scene_close_event");
	_eventDispatcher->dispatchEvent(&customEndEvent);


}
