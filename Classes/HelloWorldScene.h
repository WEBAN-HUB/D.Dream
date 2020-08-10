
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::Scene
{
public:

	Sprite* D_DREAM = nullptr;

	ActionInterval* s_action = nullptr;
	ActionInterval* s_action2 = nullptr;

	int timer = 0;

	void ScaleTimer(float t);

	void GotoPlayScene(cocos2d::Ref* pSender);

	TransitionScene* createTransition(int nIndex, float t, cocos2d::Scene* s);

    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);


	void LoadFromFile();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
