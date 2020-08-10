#pragma once

#include "cocos2d.h"
#include "extensions/cocos-ext.h"


using namespace cocos2d;
using namespace cocos2d::extension;

class StageSelect : public cocos2d::Scene, public ScrollViewDelegate
{
public:

	Sprite* stage1 = nullptr;
	Sprite* stage2 = nullptr;
	Sprite* stage3 = nullptr;
	Sprite* stage4 = nullptr;
	Sprite* stage5 = nullptr;
	Sprite* stage6 = nullptr;



	ActionInterval* s_action = nullptr;
	ActionInterval* s_action2 = nullptr;

	Action* ScreenMove = nullptr;

	Layer* tpLayer = nullptr;

	ScrollView* mpScrollView = NULL;

	virtual void scrollViewDidScroll(ScrollView* view);
	virtual void scrollViewDidZoom(ScrollView* view);
	
	//virtual bool isTouchMoved();


	virtual void update(float dt);

	Vec2 View_v;
	Vec2 setting_view;
	bool view_move = false;


	void GotoPlayScene(cocos2d::Ref* pSender);

	void GotoPlayScene2(cocos2d::Ref* pSender);
	
	void GotoPlayScene3(cocos2d::Ref* pSender);

	void GotoPlayScene4(cocos2d::Ref* pSender);

	void GotoPlayScene5(cocos2d::Ref* pSender);

	void GotoPlayScene6(cocos2d::Ref* pSender);

	void GotoSetting(cocos2d::Ref* pSender);

	TransitionScene* createTransition(int nIndex, float t, cocos2d::Scene* s);

	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(StageSelect);
};
