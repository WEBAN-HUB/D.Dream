#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class SongEnding : public cocos2d::Scene
{
public:


	ActionInterval* s_action = nullptr;
	ActionInterval* s_action2 = nullptr;


	void GotoPlayScene(cocos2d::Ref* pSender);

	void GotoStageSelect(cocos2d::Ref* pSender);

	TransitionScene* createTransition(int nIndex, float t, cocos2d::Scene* s);

	static cocos2d::Scene* createScene();

	virtual bool init();

	Label* Score;
	Label* Time;
	Label* Result;

	Sprite* StageResult_spr = nullptr;


	void SaveToFile();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(SongEnding);
};