#include "EndScene.h"
#include "Singleton_data.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "PlayScene.h"
#include "PlayScene3.h"
#include "PlayScene5.h"
#include "StageSelect.h"
#include "Singleton_sounds.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* EndScene::createScene()
{
	return EndScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool EndScene::init()
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
		CC_CALLBACK_1(EndScene::menuCloseCallback, this));

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

	Label* restart = nullptr;
	restart = Label::createWithTTF("RESTART", "fonts/bemin.ttf", 40);


	auto restartmenu = MenuItemLabel::create(
		restart,
		CC_CALLBACK_1(EndScene::GotoPlayScene, this)
	);
	restartmenu->setPosition(Vec2(240, 300));

	Label* stage = nullptr;
	stage = Label::createWithTTF("STAGE SELECT", "fonts/bemin.ttf", 40);
	

	auto stagemenu = MenuItemLabel::create(
		stage,
		CC_CALLBACK_1(EndScene::GotoStageSelect, this)
	);
	stagemenu->setPosition(Vec2(240, 200));

	Sprite* back = nullptr;
	back = Sprite::create("wall.png");
	back->setAnchorPoint(Vec2(0, 0));
	back->setPosition(0, 0);
	this->addChild(back, 0);

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, restartmenu,stagemenu, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	
	Singleton_data::getInstance()->SaveScore();

	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Singleton_sounds::getInstance()->kick_count = 0;
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(Singleton_sounds::getInstance()->Song_Volume);
	SimpleAudioEngine::getInstance()->setEffectsVolume(Singleton_sounds::getInstance()->Effect_Volume);


	Time = Label::createWithTTF("TIME:", "fonts/bemin.ttf", 60);
	Time->setColor(Color3B::ORANGE);
	
	char temp1[512];
	memset(temp1, 0, 512);
	sprintf(temp1, "TIME: %3.2f", Singleton_data::getInstance()->Time);
	std::string tString(temp1);
	Time->setString(tString);

	Time->setPosition(Vec2(240,600));
	this->addChild(Time, 1);

	Score = Label::createWithTTF("SCORE:", "fonts/bemin.ttf", 60);
	Score->setColor(Color3B::ORANGE);
	char temp2[512];
	memset(temp2, 0, 512);
	sprintf(temp2, "SCORE: %d", Singleton_data::getInstance()->Score);
	std::string tString2(temp2);
	Score->setString(tString2);

	Score->setPosition(Vec2(240, 500));
	this->addChild(Score, 1);
	
	BestScore = Label::createWithTTF("BEST SCORE", "fonts/bemin.ttf", 38);
	BestScore->setColor(Color3B::ORANGE);
	char temp3[512];
	memset(temp3, 0, 512);

	if (Singleton_data::getInstance()->Stage == 1)
	{
		sprintf(temp3, "4Beats\nBEST SCORE: %d", Singleton_data::getInstance()->BestScore_s1);
	}
	else if(Singleton_data::getInstance()->Stage == 3)
	{
		sprintf(temp3, "4Beats Hard\nBEST SCORE: %d", Singleton_data::getInstance()->BestScore_s3);
	}
	else if (Singleton_data::getInstance()->Stage == 5)
	{
		sprintf(temp3, "8Beats Hard\nBEST SCORE: %d", Singleton_data::getInstance()->BestScore_s5);
	}
	std::string tString3(temp3);
	BestScore->setString(tString3);

	BestScore->setPosition(Vec2(240, 700));
	this->addChild(BestScore, 1);
	// add "EndScene" splash screen"
	//auto sprite = Sprite::create("EndScene.png");
	//if (sprite == nullptr)
	//{
	//    problemLoading("'EndScene.png'");
	//}
	//else
	//{
	//    // position the sprite on the center of the screen
	//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	//    // add the sprite as a child to this layer
	//    this->addChild(sprite, 0);
	//}



	SaveToFile();

	return true;
}


void EndScene::SaveToFile()
{
	UserDefault::getInstance()->setIntegerForKey("key_BestScore1", Singleton_data::getInstance()->BestScore_s1);
	UserDefault::getInstance()->setIntegerForKey("key_BestScore2", Singleton_data::getInstance()->BestScore_s3);
	UserDefault::getInstance()->setIntegerForKey("key_BestScore5", Singleton_data::getInstance()->BestScore_s5);

	UserDefault::getInstance()->flush();
}

void EndScene::GotoPlayScene(Ref* pSender)
{
	if (Singleton_data::getInstance()->Stage == 1)
	{
		Singleton_sounds::getInstance()->PlayEffect(2);

		auto pScene = PlayScene::createScene();

		Director::getInstance()->replaceScene(createTransition(15, 1, pScene));
	}
	else if (Singleton_data::getInstance()->Stage == 3)
	{
		Singleton_sounds::getInstance()->PlayEffect(2);

		auto pScene = PlayScene3::createScene();

		Director::getInstance()->replaceScene(createTransition(15, 1, pScene));
	}
	else if (Singleton_data::getInstance()->Stage == 5)
	{
		Singleton_sounds::getInstance()->PlayEffect(2);

		auto pScene = PlayScene5::createScene();

		Director::getInstance()->replaceScene(createTransition(15, 1, pScene));
	}
}

void EndScene::GotoStageSelect(Ref* pSender)
{
	Singleton_sounds::getInstance()->PlayEffect(2);

	auto pScene = StageSelect::createScene();

	Director::getInstance()->replaceScene(createTransition(15, 1, pScene));

}


TransitionScene* EndScene::createTransition(int nIndex, float t, Scene* s)
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

void EndScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
