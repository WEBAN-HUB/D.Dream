
#include "SettingMenu.h"
#include "SimpleAudioEngine.h"
#include "PlayScene.h"
#include "StageSelect.h"
#include "Singleton_data.h"
#include "Singleton_sounds.h"
#include "SimpleAudioEngine.h"


using namespace CocosDenshion;

USING_NS_CC;



Scene* SettingMenu::createScene()
{
	return SettingMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SettingMenu.cpp\n");
}

// on "init" you need to initialize your instance
bool SettingMenu::init()
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


	Label* start = nullptr;

	start = Label::createWithTTF("Return to\n Stage Select", "fonts/bemin.ttf", 25);
	start->setColor(Color3B::BLACK);

	auto startmenu = MenuItemLabel::create(
		start,
		CC_CALLBACK_1(SettingMenu::GotoPlayScene, this));
	startmenu->setPosition(Vec2(340, 100));

	changesong = Label::createWithTTF("-Change Song-", "fonts/bemin.ttf", 40);
	changesong->setColor(Color3B::BLACK);

	auto csMenu = MenuItemLabel::create(
		changesong,
		CC_CALLBACK_1(SettingMenu::ChangeSong, this));
	csMenu->setPosition(Vec2(240, 700));

	songvl = Label::createWithTTF("-Song Volume-", "fonts/bemin.ttf", 40);
	songvl->setColor(Color3B::BLACK);

	auto  songvlmenu = MenuItemLabel::create(
		songvl,
		CC_CALLBACK_1(SettingMenu::songvolume, this));
	songvlmenu->setPosition(Vec2(240, 600));

	effectvl = Label::createWithTTF("-Effect Volume-", "fonts/bemin.ttf", 40);
	effectvl->setColor(Color3B::BLACK);

	auto effectvlmenu = MenuItemLabel::create(
		effectvl,
		CC_CALLBACK_1(SettingMenu::effectvolume, this));
	effectvlmenu->setPosition(Vec2(240, 500));

	kicktype = Label::createWithTTF("KICK TYPE :", "fonts/bemin.ttf", 30);
	kicktype->setColor(Color3B::BLACK);

	auto kickmenu = MenuItemLabel::create(
		kicktype,
		CC_CALLBACK_1(SettingMenu::Kickchange, this));

	kickmenu->setPosition(Vec2(150, 350));

	snaretype = Label::createWithTTF("SNARE TYPE: ", "fonts/bemin.ttf", 30);
	snaretype->setColor(Color3B::BLACK);

	auto snaremenu = MenuItemLabel::create(
		snaretype,
		CC_CALLBACK_1(SettingMenu::Snarechange,this));

	snaremenu->setPosition(Vec2(150, 280));


	hattype = Label::createWithTTF("HIHAT TYPE: ", "fonts/bemin.ttf", 30);
	hattype->setColor(Color3B::BLACK);

	auto hatmenu = MenuItemLabel::create(
		hattype,
		CC_CALLBACK_1(SettingMenu::Hatchange, this));

	hatmenu->setPosition(Vec2(150, 210));

	// create menu, it's an autorelease object
	auto menu = Menu::create(startmenu,csMenu,songvlmenu,effectvlmenu,kickmenu,snaremenu,hatmenu, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	Sprite* back = nullptr;
	back = Sprite::create("setting.jpg");
	back->setAnchorPoint(Vec2(0, 0));
	back->setPosition(0, 0);
	this->addChild(back, 0);

	songname = Label::createWithTTF("- Dream..", "fonts/bemin.ttf", 30);
	songname->setColor(Color3B::BLACK);
	songname->setPosition(Vec2(240, 650));
	this->addChild(songname, 10);

	svlview = Label::createWithTTF(" ", "fonts/bemin.ttf", 30);
	svlview->setColor(Color3B::BLACK);
	svlview->setPosition(Vec2(240, 550));
	this->addChild(svlview, 10);
	
	char temp1[512];
	memset(temp1, 0, 512);
	sprintf(temp1, "volume level:%3.0f", Singleton_sounds::getInstance()->Song_Volume * 100);
	std::string tString = temp1;
	svlview->setString(tString);


	evlview = Label::createWithTTF(" ", "fonts/bemin.ttf", 30);
	evlview->setColor(Color3B::BLACK);
	evlview->setPosition(Vec2(240, 450));
	this->addChild(evlview, 10);


	char temp2[512];
	memset(temp2, 0, 512);
	sprintf(temp2, "volume level:%3.0f", Singleton_sounds::getInstance()->Effect_Volume * 100);
	std::string tString2 = temp2;
	evlview->setString(tString2);
	


	kicktype_v = Label::createWithTTF(" A ", "fonts/bemin.ttf", 30);
	kicktype_v->setColor(Color3B::BLACK);
	kicktype_v->setPosition(Vec2(300, 350));
	this->addChild(kicktype_v,10);


	if (Singleton_sounds::getInstance()->KS == 0)
	{
		kicktype_v->setString(" -A- ");
	}
	else if (Singleton_sounds::getInstance()->KS == 3)
	{
		kicktype_v->setString(" -B- ");
	}
	else if (Singleton_sounds::getInstance()->KS == 6)
	{
		kicktype_v->setString(" -C- ");
	}


	snaretype_v = Label::createWithTTF(" B ", "fonts/bemin.ttf", 30);
	snaretype_v->setColor(Color3B::BLACK);
	snaretype_v->setPosition(Vec2(300, 280));
	this->addChild(snaretype_v,10);

	if (Singleton_sounds::getInstance()->SS == 1)
	{
		snaretype_v->setString(" -A- ");
	}
	else if (Singleton_sounds::getInstance()->SS == 4)
	{
		snaretype_v->setString(" -B- ");
	}
	else if (Singleton_sounds::getInstance()->SS == 7)
	{
		snaretype_v->setString(" -C- ");
	}

	hattype_v = Label::createWithTTF(" A ", "fonts/bemin.ttf", 30);
	hattype_v->setColor(Color3B::BLACK);
	hattype_v->setPosition(Vec2(300, 210));
	this->addChild(hattype_v, 10);

	if (Singleton_sounds::getInstance()->HS == 2)
	{
		hattype_v->setString(" -A- ");
	}
	else if (Singleton_sounds::getInstance()->HS == 5)
	{
		hattype_v->setString(" -B- ");
	}
	else if (Singleton_sounds::getInstance()->HS == 8)
	{
		hattype_v->setString(" -C- ");
	}





	if (Singleton_sounds::getInstance()->MS == 0)
	{
		songname->setString("Dream..");
	}
	else if (Singleton_sounds::getInstance()->MS == 1)
	{
		songname->setString("MIDNIGHT CITY");
	}
	else if (Singleton_sounds::getInstance()->MS == 2)
	{
		songname->setString("Vacation");
	}



	return true;
}





void SettingMenu::Kickchange(cocos2d::Ref* pSender)
{

	if (Singleton_sounds::getInstance()->KS == 0)
	{
		Singleton_sounds::getInstance()->KS = 3;
		kicktype_v->setString(" -B- ");
		Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->KS);
	}
	else if (Singleton_sounds::getInstance()->KS == 3)
	{
		Singleton_sounds::getInstance()->KS = 6;
		kicktype_v->setString(" -C- ");
		Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->KS);
	}
	else if (Singleton_sounds::getInstance()->KS == 6)
	{
		Singleton_sounds::getInstance()->KS = 0;
		kicktype_v->setString(" -A- ");
		Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->KS);
	}


}


void SettingMenu::Snarechange(cocos2d::Ref* pSender)
{

	if (Singleton_sounds::getInstance()->SS == 1)
	{
		Singleton_sounds::getInstance()->SS = 4;
		snaretype_v->setString(" -B- ");
		Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->SS);
	}
	else if (Singleton_sounds::getInstance()->SS == 4)
	{
		Singleton_sounds::getInstance()->SS = 7;
		snaretype_v->setString(" -C- ");
		Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->SS);
	}
	else if (Singleton_sounds::getInstance()->SS == 7)
	{
		Singleton_sounds::getInstance()->SS = 1;
		snaretype_v->setString(" -A- ");
		Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->SS);
	}


}

void SettingMenu::Hatchange(cocos2d::Ref* pSender)
{

	if (Singleton_sounds::getInstance()->HS == 2)
	{
		Singleton_sounds::getInstance()->HS = 5;
		hattype_v->setString(" -B- ");
		Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->HS);
	}
	else if (Singleton_sounds::getInstance()->HS == 5)
	{
		Singleton_sounds::getInstance()->HS = 8;
		hattype_v->setString(" -C- ");
		Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->HS);
	}
	else if (Singleton_sounds::getInstance()->HS == 8)
	{
		Singleton_sounds::getInstance()->HS = 2;
		hattype_v->setString(" -A- ");
		Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->HS);
	}




}




void SettingMenu::songvolume(cocos2d::Ref* pSender)
{
	Singleton_sounds::getInstance()->Song_Volume = Singleton_sounds::getInstance()->Song_Volume + 0.1;
	if (Singleton_sounds::getInstance()->Song_Volume >= 1.1)
	{
		Singleton_sounds::getInstance()->Song_Volume = 0;
	}

	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(Singleton_sounds::getInstance()->Song_Volume);

	char temp3[512];
	memset(temp3, 0, 512);
	sprintf(temp3, "volume level:%3.0f", Singleton_sounds::getInstance()->Song_Volume * 100);
	std::string tString3 = temp3;
	svlview->setString(tString3);


	log("%f", Singleton_sounds::getInstance()->Song_Volume);
}


void SettingMenu::effectvolume(cocos2d::Ref* pSender)
{
	Singleton_sounds::getInstance()->Effect_Volume = Singleton_sounds::getInstance()->Effect_Volume + 0.1;
	if (Singleton_sounds::getInstance()->Effect_Volume >= 1.1)
	{
		Singleton_sounds::getInstance()->Effect_Volume = 0;
	}

	SimpleAudioEngine::getInstance()->setEffectsVolume(Singleton_sounds::getInstance()->Effect_Volume);

	char temp4[512];
	memset(temp4, 0, 512);
	sprintf(temp4, "volume level:%3.0f", Singleton_sounds::getInstance()->Effect_Volume * 100);
	std::string tString4 = temp4;
	evlview->setString(tString4);

	Singleton_sounds::getInstance()->PlayEffect(0);

	log("%f", Singleton_sounds::getInstance()->Effect_Volume);

}



void SettingMenu::ChangeSong(Ref* pSender)
{

	SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	
	Singleton_sounds::getInstance()->MS++;
	if (Singleton_sounds::getInstance()->MS == 3)
	{
		Singleton_sounds::getInstance()->MS = 0;
	}

	if (Singleton_sounds::getInstance()->MS == 0)
	{
		songname->setString("Dream..");
	}
	else if (Singleton_sounds::getInstance()->MS == 1)
	{
		songname->setString("MIDNIGHT CITY");
	}
	else if (Singleton_sounds::getInstance()->MS == 2)
	{
		songname->setString("Vacation");
	}


	Singleton_sounds::getInstance()->PlayBGM();

}


void SettingMenu::ScaleTimer(float t)
{


}

void SettingMenu::GotoPlayScene(Ref* pSender)
{
	Singleton_sounds::getInstance()->PlayEffect(2);

	auto pScene = StageSelect::createScene();

	Director::getInstance()->replaceScene(createTransition(15, 1, pScene));

}


TransitionScene* SettingMenu::createTransition(int nIndex, float t, Scene* s)
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

void SettingMenu::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
