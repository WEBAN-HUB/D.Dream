#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class SettingMenu : public cocos2d::Scene
{
public:
	Label* changesong = nullptr;
	Label* songname = nullptr;

	Label* songvl = nullptr;
	Label* svlview = nullptr;

	Label* effectvl = nullptr;
	Label* evlview = nullptr;

	Label* kicktype = nullptr;
	Label* kicktype_v = nullptr;

	Label* snaretype = nullptr;
	Label* snaretype_v = nullptr;

	Label* hattype = nullptr;
	Label* hattype_v = nullptr;

	int timer = 0;

	void ScaleTimer(float t);

	void GotoPlayScene(cocos2d::Ref* pSender);

	void ChangeSong(cocos2d::Ref* pSender);

	void songvolume(cocos2d::Ref* pSender);

	void effectvolume(cocos2d::Ref* pSender);

	void Kickchange(cocos2d::Ref* pSender);

	void Snarechange(cocos2d::Ref* pSender);

	void Hatchange(cocos2d::Ref* pSender);

	TransitionScene* createTransition(int nIndex, float t, cocos2d::Scene* s);

	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(SettingMenu);
};