#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class EndScene : public cocos2d::Scene
{
public:

	void GotoPlayScene(cocos2d::Ref* pSender);

	void GotoStageSelect(cocos2d::Ref* pSender);

	TransitionScene* createTransition(int nIndex, float t, cocos2d::Scene* s);

	static cocos2d::Scene* createScene();

	virtual bool init();

	Label* Score;
	Label* Time;
	Label* BestScore;

	void SaveToFile();


	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(EndScene);
};