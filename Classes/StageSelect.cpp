#include "StageSelect.h"

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "PlayScene.h"
#include "PlayScene2.h"
#include "PlayScene3.h"
#include "PlayScene4.h"
#include "PlayScene5.h"
#include "PlayScene6.h"
#include "SettingMenu.h"
#include "Singleton_sounds.h"
#include "Singleton_data.h"


using namespace CocosDenshion;

USING_NS_CC;

Scene* StageSelect::createScene()
{
	return StageSelect::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool StageSelect::init()
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
		CC_CALLBACK_1(StageSelect::menuCloseCallback, this));

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

	Label* stage1b = nullptr;
	stage1b = Label::createWithTTF("Play", "fonts/bemin.ttf", 50);
	

	auto stage1menu = MenuItemLabel::create(
		stage1b,
		CC_CALLBACK_1(StageSelect::GotoPlayScene, this));
	stage1menu->setPosition(Vec2(240, 300));

	Label* stage2b = nullptr;
	stage2b = Label::createWithTTF("Play", "fonts/bemin.ttf", 50);
	

	auto stage2menu = MenuItemLabel::create(
		stage2b,
		CC_CALLBACK_1(StageSelect::GotoPlayScene2, this));
	stage2menu->setPosition(Vec2(720, 300));

	Label* stage3b = nullptr;
	stage3b = Label::createWithTTF("Play", "fonts/bemin.ttf", 50);


	auto stage3menu = MenuItemLabel::create(
		stage3b,
		CC_CALLBACK_1(StageSelect::GotoPlayScene3, this));
	stage3menu->setPosition(Vec2(1200, 300));

	Label* stage4b = nullptr;
	stage4b = Label::createWithTTF("Play", "fonts/bemin.ttf", 50);
	stage4b->setColor(Color3B::ORANGE);
	

	auto stage4menu = MenuItemLabel::create(
		stage4b,
		CC_CALLBACK_1(StageSelect::GotoPlayScene4, this));
	stage4menu->setPosition(Vec2(1680, 300));


	Label* stage5b = nullptr;
	stage5b = Label::createWithTTF("Play", "fonts/bemin.ttf", 50);


	auto stage5menu = MenuItemLabel::create(
		stage5b,
		CC_CALLBACK_1(StageSelect::GotoPlayScene5, this));
	stage5menu->setPosition(Vec2(2160, 300));

	Label* stage6b = nullptr;
	stage6b = Label::createWithTTF("Play", "fonts/bemin.ttf", 50);


	auto stage6menu = MenuItemLabel::create(
		stage6b,
		CC_CALLBACK_1(StageSelect::GotoPlayScene6, this));
	stage6menu->setPosition(Vec2(2640, 300));

	auto label = Label::createWithTTF("-Setting Menu-", "fonts/bemin.ttf", 40);
	
	Label* label2 = Label::createWithTTF("-EXIT-", "fonts/bemin.ttf", 40);

	auto settingmenu = MenuItemLabel::create(
		label,
		CC_CALLBACK_1(StageSelect::GotoSetting, this));
	settingmenu->setPosition(Vec2(240, 150));

	auto exitmenu = MenuItemLabel::create(
		label2,
		CC_CALLBACK_1(StageSelect::menuCloseCallback, this));
	exitmenu->setPosition(Vec2(240, 100));

	auto Fix_menu = Menu::create(settingmenu,exitmenu, nullptr);
	Fix_menu->setPosition(Vec2::ZERO);

	this->addChild(Fix_menu,20);

	// create menu, it's an autorelease object
	auto menu = Menu::create(stage1menu,stage2menu,stage3menu,stage4menu, stage5menu,stage6menu, NULL);
	menu->setPosition(Vec2::ZERO);
	/*this->addChild(menu, 1);*/

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label




	stage1 = Sprite::create("stage1.png");
	stage2 = Sprite::create("stage2.png");
	stage3 = Sprite::create("stage3.png");
	stage4 = Sprite::create("stage4.png");
	stage5 = Sprite::create("stage5.png");
	stage6 = Sprite::create("stage6.png");
	Sprite* Layerback = Sprite::create("select.jpg");
	Layerback->setAnchorPoint(Point(0,  0));

	Sprite* Layerback2 = Sprite::create("select3.jpg");
	Layerback2->setAnchorPoint(Point(0, 0));

	stage1->setScale(0.3);
	stage2->setScale(0.3);
	stage3->setScale(0.3);
	stage4->setScale(0.3);
	stage5->setScale(0.3);
	stage6->setScale(0.3);

	stage1->setPosition(Point(240, 600));
	stage2->setPosition(Point(720, 600));
	stage3->setPosition(Point(1200,600));
	stage4->setPosition(Point(1680, 600));
	stage5->setPosition(Point(2160, 600));
	stage6->setPosition(Point(2640, 600));
	Layerback->setPosition(Point(-700, 0));
	Layerback2->setPosition(Point(0, 0));



	tpLayer = Layer::create();
	tpLayer->setAnchorPoint(Point::ZERO);
	tpLayer->setPosition(Point(0, 0));
	tpLayer->setContentSize(Size(2880, 800));

	tpLayer->addChild(Layerback,0);
	tpLayer->addChild(Layerback2, 0);
	tpLayer->addChild(menu,2);
	tpLayer->addChild(stage1,2);
	tpLayer->addChild(stage2,2);
	tpLayer->addChild(stage3,2);
	tpLayer->addChild(stage4,2);
	tpLayer->addChild(stage5,2);
	tpLayer->addChild(stage6,2);
	


	if (Singleton_data::getInstance()->stage1_c == true)
	{
		Label* stage1c = nullptr;
		stage1c = Label::createWithTTF("CLEAR!", "fonts/bemin.ttf", 50);
		stage1c->setColor(Color3B::RED);
		
		stage1c->setPosition(Point(720, 420));
		tpLayer->addChild(stage1c, 3);
	}
	else
	{
		Label* stage1c = nullptr;
		stage1c = Label::createWithTTF("", "fonts/bemin.ttf", 60);
		stage1c->setColor(Color3B::ORANGE);

		stage1c->setPosition(Point(720, 400));
		tpLayer->addChild(stage1c, 3);

		char ptemp[512];
		memset(ptemp, 0, 512);
		sprintf(ptemp, "%d%%",Singleton_data::getInstance()->song1p );
		std::string pString(ptemp);
		stage1c->setString(pString);

	}

	if (Singleton_data::getInstance()->stage2_c == true)
	{
		Label* stage2c = nullptr;
		stage2c = Label::createWithTTF("CLEAR!", "fonts/bemin.ttf", 50);
		stage2c->setColor(Color3B::RED);
	
		stage2c->setPosition(Point(1680, 420));
		tpLayer->addChild(stage2c, 3);
	}
	else
	{
		Label* stage2c = nullptr;
		stage2c = Label::createWithTTF("CLEAR!", "fonts/bemin.ttf", 60);
		stage2c->setColor(Color3B::ORANGE);

		stage2c->setPosition(Point(1680, 400));
		tpLayer->addChild(stage2c, 3);

		char ptemp[512];
		memset(ptemp, 0, 512);
		sprintf(ptemp, "%d%%", Singleton_data::getInstance()->song2p);
		std::string pString(ptemp);
		stage2c->setString(pString);
	}

	if (Singleton_data::getInstance()->stage3_c == true)
	{
		Label* stage3c = nullptr;
		stage3c = Label::createWithTTF("CLEAR!", "fonts/bemin.ttf", 50);
		stage3c->setColor(Color3B::RED);
		stage3c->setPosition(Point(2640, 420));
		tpLayer->addChild(stage3c, 3);
	
	}
	else
	{
		Label* stage3c = nullptr;
		stage3c = Label::createWithTTF("CLEAR!", "fonts/bemin.ttf", 60);
		stage3c->setColor(Color3B::ORANGE);
		stage3c->setPosition(Point(2640, 400));
		tpLayer->addChild(stage3c, 3);

		char ptemp[512];
		memset(ptemp, 0, 512);
		sprintf(ptemp, "%d%%", Singleton_data::getInstance()->song3p);
		std::string pString(ptemp);
		stage3c->setString(pString);

	}







	s_action = ScaleTo::create(1, 0.4);
	s_action2 = ScaleTo::create(1, 0.3);

	auto tSequence = Sequence::create(s_action, s_action2, nullptr);

	RepeatForever* tRepeatForever = RepeatForever::create(tSequence);



	stage1->runAction(tRepeatForever);
	stage2->runAction(tRepeatForever->clone());
	stage3->runAction(tRepeatForever->clone());
	stage4->runAction(tRepeatForever->clone());
	stage5->runAction(tRepeatForever->clone());
	stage6->runAction(tRepeatForever->clone());




	mpScrollView = ScrollView::create();
	mpScrollView->retain();

	mpScrollView->setDirection(ScrollView::Direction::HORIZONTAL);

	mpScrollView->setViewSize(Size(480, 800));
	mpScrollView->setContentSize(tpLayer->getContentSize());
	mpScrollView->setContentOffset(Point::ZERO, false);

	mpScrollView->setPosition(Point(0, 0));
	mpScrollView->setContainer(tpLayer);
	mpScrollView->setBounceable(false);

	mpScrollView->setDelegate(this);


	

	this->addChild(mpScrollView);

	this->scheduleUpdate();


	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying() == false) 
	{

		Singleton_sounds::getInstance()->PlayBGM();
	}
	return true;
}

void StageSelect::GotoPlayScene(Ref* pSender)
{
	Singleton_sounds::getInstance()->PlayEffect(2);


	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0);

	Singleton_sounds::getInstance()->PlayBGM();

	SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(Singleton_sounds::getInstance()->Song_Volume);


	auto pScene = PlayScene::createScene();

	Director::getInstance()->replaceScene(createTransition(15, 1, pScene));

}

void StageSelect::GotoPlayScene2(Ref* pSender)
{

	Singleton_sounds::getInstance()->PlayEffect(2);


	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0);

	Singleton_sounds::getInstance()->PlayBGM();

	SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(Singleton_sounds::getInstance()->Song_Volume);


	auto pScene = PlayScene2::createScene();

	Director::getInstance()->replaceScene(createTransition(15, 1, pScene));
}

void StageSelect::GotoPlayScene3(Ref* pSender)
{
	Singleton_sounds::getInstance()->PlayEffect(2);

	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0);

	Singleton_sounds::getInstance()->PlayBGM();

	SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(Singleton_sounds::getInstance()->Song_Volume);



	auto pScene = PlayScene3::createScene();

	Director::getInstance()->replaceScene(createTransition(15, 1, pScene));
}

void StageSelect::GotoPlayScene4(Ref* pSender)
{

	Singleton_sounds::getInstance()->PlayEffect(2);


	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0);

	Singleton_sounds::getInstance()->PlayBGM();

	SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(Singleton_sounds::getInstance()->Song_Volume);


	auto pScene = PlayScene4::createScene();

	Director::getInstance()->replaceScene(createTransition(15, 1, pScene));
}



void StageSelect::GotoPlayScene5(Ref* pSender)
{
	Singleton_sounds::getInstance()->PlayEffect(2);


	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0);

	Singleton_sounds::getInstance()->PlayBGM();

	SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(Singleton_sounds::getInstance()->Song_Volume);


	auto pScene = PlayScene5::createScene();

	Director::getInstance()->replaceScene(createTransition(15, 1, pScene));
}


void StageSelect::GotoPlayScene6(Ref* pSender)
{
	Singleton_sounds::getInstance()->PlayEffect(2);

	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0);

	Singleton_sounds::getInstance()->PlayBGM();

	SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(Singleton_sounds::getInstance()->Song_Volume);


	auto pScene = PlayScene6::createScene();

	Director::getInstance()->replaceScene(createTransition(15, 1, pScene));
}

void StageSelect::GotoSetting(Ref* pSender)
{
	auto pScene = SettingMenu::createScene();

	Director::getInstance()->replaceScene(createTransition(15, 1, pScene));
}

void StageSelect::update(float dt)
{
	if ( view_move == false && View_v.x > -240)
	{
		setting_view = View_v;
		setting_view.x = 0;
		mpScrollView->setContentOffsetInDuration(setting_view, 0.1f);
		view_move = true;
	}
	else if (view_move == false && View_v.x > -720 && View_v.x <= -240)
	{
		setting_view = View_v;
		setting_view.x = -480;
		mpScrollView->setContentOffsetInDuration(setting_view, 0.1f);
		view_move = true;
	}
	else if (view_move == false && View_v.x > -1200 && View_v.x <= -740)
	{
		setting_view = View_v;
		setting_view.x = -960;
		mpScrollView->setContentOffsetInDuration(setting_view, 0.1f);
		view_move = true;
	}
	else if (view_move == false && View_v.x > -1680 && View_v.x <= 1200)
	{
		setting_view = View_v;
		setting_view.x = -1440;
		mpScrollView->setContentOffsetInDuration(setting_view, 0.1f);
		view_move = true;
	}
	else if (view_move == false && View_v.x > -2160 && View_v.x <= 1680)
	{
		setting_view = View_v;
		setting_view.x = -1920;
		mpScrollView->setContentOffsetInDuration(setting_view, 0.1f);
		view_move = true;
	}
	else if (view_move == false && View_v.x <= -2160)
	{
		setting_view = View_v;
		setting_view.x = -2400;
		mpScrollView->setContentOffsetInDuration(setting_view, 0.1f);
		view_move = true;
	}

}

void StageSelect::scrollViewDidScroll(ScrollView* view)
{
	
	/*log(("%d"),stage1->getPositionX());*/


	if (view->isTouchMoved() == false)
	{
		view_move = false;
	}
	else if (view->isTouchMoved() == true)
	{
		view_move = true;
	}

	View_v = view->getContentOffset();
	


	
}


void StageSelect::scrollViewDidZoom(ScrollView* view)
{

}

//bool StageSelect::isTouchMoved()
//{
//
//}
//


TransitionScene* StageSelect::createTransition(int nIndex, float t, Scene* s)
{
	Director::getInstance()->setDepthTest(false);

	switch (nIndex)
	{
		// 점프하면서 Zoom
	case 0: return TransitionJumpZoom::create(t, s);


		// 시계방향으로 침이 돌면서 장면이 바뀜
	case 1: return TransitionProgressRadialCCW::create(t, s);
		// 시계반대방향으로 침이 돌면서 장면이 바뀜
	case 2: return TransitionProgressRadialCW::create(t, s);
	case 3: return TransitionProgressHorizontal::create(t, s);
	case 4: return TransitionProgressVertical::create(t, s);
	case 5: return TransitionProgressInOut::create(t, s);
	case 6: return TransitionProgressOutIn::create(t, s);

		// 교차
	case 7: return TransitionCrossFade::create(t, s);


		// 페이지넘김형식 : PageTransitionForward
	case 8: return TransitionPageTurn::create(t, s, false);
		// 페이지넘김형식 : PageTransitionBackward
	case 9: return TransitionPageTurn::create(t, s, true);
		// 바둑판무늬 좌측하단부터 우측상단순으로 사라짐
	case 10: return TransitionFadeTR::create(t, s);
		// 바툭판무늬 우측상단부터 좌측하단순으로 사라짐
	case 11: return TransitionFadeBL::create(t, s);
		// 하단에서 상단으로 잘라냄
	case 12: return TransitionFadeUp::create(t, s);
		// 상단에서 하단으로 잘라냄
	case 13: return TransitionFadeDown::create(t, s);


		// 바둑판무늬 뿌리기
	case 14: return TransitionTurnOffTiles::create(t, s);


		// 가로로 세등분 나눔
	case 15: return TransitionSplitRows::create(t, s);
		// 세로로 세등분 나눔, 양끝의 두둥분은 밑으로 나머지는 위로
	case 16: return TransitionSplitCols::create(t, s);


		// 페이드인아웃 : 검정 화면
	case 17: return TransitionFade::create(t, s);
		// 페이드인아웃 : 하얀 화면
	case 18: return TransitionFade::create(t, s, Color3B::WHITE);


		// X축(횡선)을 기준으로 회전 : FlipXLeftOver
	case 19: return TransitionFlipX::create(t, s, TransitionScene::Orientation::LEFT_OVER);
		// X축(횡선)을 기준으로 회전 : FlipXRightOver
	case 20: return TransitionFlipX::create(t, s, TransitionScene::Orientation::RIGHT_OVER);
		// Y축(종선)을 기준으로 회전 : FlipYUpOver
	case 21: return TransitionFlipY::create(t, s, TransitionScene::Orientation::UP_OVER);
		// Y축(종선)을 기준으로 회전 : FlipYDownOver
	case 22: return TransitionFlipY::create(t, s, TransitionScene::Orientation::DOWN_OVER);
		// 뒤집어지면서 다음장면으로 넘어감 : FlipAngularLeftOver
	case 23: return TransitionFlipAngular::create(t, s, TransitionScene::Orientation::LEFT_OVER);
		// 뒤집어지면서 다음장면으로 넘어감 : FlipAngularRightOver
	case 24: return TransitionFlipAngular::create(t, s, TransitionScene::Orientation::RIGHT_OVER);


		// X축(횡선)을 기준으로 회전 (확대) : ZoomFlipXLeftOver
	case 25: return TransitionZoomFlipX::create(t, s, TransitionScene::Orientation::LEFT_OVER);
		// X축(횡선)을 기준으로 회전 (확대) : ZoomFlipXRightOver
	case 26: return TransitionZoomFlipX::create(t, s, TransitionScene::Orientation::RIGHT_OVER);
		// Y축(종선)을 기준으로 회전 (확대) : ZoomFlipYUpOver
	case 27: return TransitionZoomFlipY::create(t, s, TransitionScene::Orientation::UP_OVER);
		// Y축(종선)을 기준으로 회전 (확대) : ZoomFlipYDownOver
	case 28: return TransitionZoomFlipY::create(t, s, TransitionScene::Orientation::DOWN_OVER);
		// 뒤집어지면서 다음장면으로 넘어감 (확대) : ZoomFlipAngularLeftOver
	case 29: return TransitionZoomFlipAngular::create(t, s, TransitionScene::Orientation::LEFT_OVER);
		// 뒤집어지면서 다음장면으로 넘어감 (확대) : ZoomFlipAngularRightOver
	case 30: return TransitionZoomFlipAngular::create(t, s, TransitionScene::Orientation::RIGHT_OVER);


		// 이전장면 수축 다음장면 확대
	case 31: return TransitionShrinkGrow::create(t, s);
		// 회전하면서 Zoom
	case 32: return TransitionRotoZoom::create(t, s);


		// 왼쪽에서 다음장면이 나타나서 이전장면을 덮어씀
	case 33: return TransitionMoveInL::create(t, s);
		// 오른쪽에서 다음장면이 나타남
	case 34: return TransitionMoveInR::create(t, s);
		// 위쪽에서 다음장면이 나타남
	case 35: return TransitionMoveInT::create(t, s);
		// 아래쪽에서 다음장면이 나타남
	case 36: return TransitionMoveInB::create(t, s);


		// 왼쪽에서 다음장면이 나타나서 이전장면을 밀어냄
	case 37: return TransitionSlideInL::create(t, s);
		// 오른쪽에서 다음장면이 나타나서 이전장면을 밀어냄
	case 38: return TransitionSlideInR::create(t, s);
		// 위쪽에서 다음장면이 나타나서 이전장면을 밀어냄
	case 39: return TransitionSlideInT::create(t, s);
		// 아래쪽에서 다음장면이 나타나서 이전장면을 밀어냄
	case 40: return TransitionSlideInB::create(t, s);

	default: break;
	}

	return NULL;
}

void StageSelect::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
