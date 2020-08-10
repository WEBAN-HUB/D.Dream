#pragma once

#include "cocos2d.h"


using namespace cocos2d;

class NormalNote;
class KickNote;
class SnareNote;

class PlayScene6 : public cocos2d::Scene
{
private:

	int normal_count = 0;

	int snare_count = 0;

	int kick_count = 0;


	Sprite* barspr = nullptr;
	Sprite* barspr2 = nullptr;
	Vec2 barv;
	void bartimer(float t);
	float bar_count = 0.0f;



public:

	Sprite* mpSpriteA = nullptr;
	Sprite* mpSpriteB = nullptr;
	Sprite* mpSpriteC = nullptr;

	Sprite* back = nullptr;
	Vec2 backV;

	NormalNote* normalnote[9] = { nullptr, };

	KickNote* kicknote[3] = { nullptr, };
	SnareNote* snarenote =  nullptr;

	Label* Time = nullptr;
	Label* Score = nullptr;

	void update_stat(float dt);

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);

	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);



	EventListenerTouchOneByOne* mpListener = nullptr;

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);


	EventListenerTouchAllAtOnce* multiListener = nullptr;

	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event* event);








	virtual  void update(float dt);

	void OnTimer(float f);

	void kicktimer(float t);

	void snaretimer(float t);

	static cocos2d::Scene* createScene();

	virtual bool init();

	void die_ending();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(PlayScene6);
};
