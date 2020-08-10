
#include "SongEnding.h"
#include "Singleton_data.h"
#include "Singleton_sounds.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "PlayScene2.h"
#include "PlayScene4.h"
#include "PlayScene6.h"
#include "StageSelect.h"

USING_NS_CC;
using namespace CocosDenshion;


Scene* SongEnding::createScene()
{
	return SongEnding::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SongEnding::init()
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
		CC_CALLBACK_1(SongEnding::menuCloseCallback, this));

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
		CC_CALLBACK_1(SongEnding::GotoPlayScene, this)
	);
	restartmenu->setPosition(Vec2(240, 300));

	Label* stage = nullptr;
	stage = Label::createWithTTF("STAGE SELECT", "fonts/bemin.ttf", 40);
	

	auto stagemenu = MenuItemLabel::create(
		stage,
		CC_CALLBACK_1(SongEnding::GotoStageSelect, this)
	);
	stagemenu->setPosition(Vec2(240, 200));

	Sprite* back = nullptr;
	back = Sprite::create("wall.png");
	back->setAnchorPoint(Vec2(0, 0));
	back->setPosition(0, 0);
	this->addChild(back, 0);


	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem,restartmenu,stagemenu, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	if (Singleton_data::getInstance()->Life >= 1)
	{
		Result = Label::createWithTTF("SONG \nCLEAR!", "fonts/bemin.ttf", 46);
		Result->setColor(Color3B::ORANGE);
		Result->setPosition(Vec2(240, 650));
		this->addChild(Result, 0);

		if (Singleton_data::getInstance()->Stage == 2)
		{
			Singleton_data::getInstance()->stage1_c = true;
		}
		else if(Singleton_data::getInstance()->Stage == 4)
		{ 
			Singleton_data::getInstance()->stage2_c = true;
		}
		else if (Singleton_data::getInstance()->Stage == 6)
		{
			Singleton_data::getInstance()->stage3_c = true;
		}
	}
	else if (Singleton_data::getInstance()->Life < 1)
	{
		Result = Label::createWithTTF("", "fonts/bemin.ttf", 46);
		Result->setColor(Color3B::ORANGE);
		Result->setPosition(Vec2(240, 480));
		this->addChild(Result, 0);

		Label* Result2 = Label::createWithTTF("", "fonts/bemin.ttf", 60);
		Result2->setColor(Color3B::BLUE);
		Result2->setPosition(Vec2(240, 680));
		this->addChild(Result2, 0);

		char ptemp2[512];
		memset(ptemp2, 0, 512);
		sprintf(ptemp2, "%d%%", Singleton_data::getInstance()->percent);
		std::string pString2(ptemp2);
		Result->setString(pString2);

		if (Singleton_data::getInstance()->Stage == 2)
		{
			char ptemp[512];
			memset(ptemp, 0, 512);
			sprintf(ptemp, "BEST\n   %d%%", Singleton_data::getInstance()->song1p);
			std::string pString(ptemp);
			Result2->setString(pString);
		}
		else if (Singleton_data::getInstance()->Stage == 4)
		{
			char ptemp[512];
			memset(ptemp, 0, 512);
			sprintf(ptemp, "BEST\n   %d%%", Singleton_data::getInstance()->song2p);
			std::string pString(ptemp);
			Result2->setString(pString);
		}
		else if (Singleton_data::getInstance()->Stage == 6)
		{
			char ptemp[512];
			memset(ptemp, 0, 512);
			sprintf(ptemp, "BEST\n   %d%%", Singleton_data::getInstance()->song3p);
			std::string pString(ptemp);
			Result2->setString(pString);
		}


	}




	s_action = ScaleTo::create(1, 2);
	s_action2 = ScaleTo::create(1, 1.5);

	auto tSequence = Sequence::create(s_action,s_action2,nullptr);

	RepeatForever* tRepeatForever = RepeatForever::create(tSequence);


	Result->runAction(tRepeatForever);



	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Singleton_sounds::getInstance()->kick_count = 0;
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(Singleton_sounds::getInstance()->Song_Volume);
	SimpleAudioEngine::getInstance()->setEffectsVolume(Singleton_sounds::getInstance()->Effect_Volume);

	SaveToFile();

	return true;
}

void SongEnding::SaveToFile()
{
	UserDefault::getInstance()->setBoolForKey("key_stagec1", Singleton_data::getInstance()->stage1_c);
	UserDefault::getInstance()->setBoolForKey("key_stagec2", Singleton_data::getInstance()->stage2_c);
	UserDefault::getInstance()->setBoolForKey("key_stagec3", Singleton_data::getInstance()->stage3_c);
	UserDefault::getInstance()->setIntegerForKey("key_song1p", Singleton_data::getInstance()->song1p);
	UserDefault::getInstance()->setIntegerForKey("key_song2p", Singleton_data::getInstance()->song2p);
	UserDefault::getInstance()->setIntegerForKey("key_song3p", Singleton_data::getInstance()->song3p);



}

void SongEnding::GotoPlayScene(Ref* pSender)
{
	
	if (Singleton_data::getInstance()->Stage == 2)
	{
		Singleton_sounds::getInstance()->PlayEffect(2);

		auto pScene = PlayScene2::createScene();

		Director::getInstance()->replaceScene(createTransition(15, 1, pScene));
	}
	else if (Singleton_data::getInstance()->Stage == 4)
	{
		Singleton_sounds::getInstance()->PlayEffect(2);

		auto pScene = PlayScene4::createScene();

		Director::getInstance()->replaceScene(createTransition(15, 1, pScene));
	}
	else if (Singleton_data::getInstance()->Stage == 6)
	{
		Singleton_sounds::getInstance()->PlayEffect(2);

		auto pScene = PlayScene6::createScene();

		Director::getInstance()->replaceScene(createTransition(15, 1, pScene));
	}

}

void SongEnding::GotoStageSelect(Ref* pSender)
{
	Singleton_sounds::getInstance()->PlayEffect(2);

	auto pScene = StageSelect::createScene();

	Director::getInstance()->replaceScene(createTransition(15, 1, pScene));

}


TransitionScene* SongEnding::createTransition(int nIndex, float t, Scene* s)
{
	Director::getInstance()->setDepthTest(false);

	switch (nIndex)
	{
		// �����ϸ鼭 Zoom
	case 0: return TransitionJumpZoom::create(t, s);


		// �ð�������� ħ�� ���鼭 ����� �ٲ�
	case 1: return TransitionProgressRadialCCW::create(t, s);
		// �ð�ݴ�������� ħ�� ���鼭 ����� �ٲ�
	case 2: return TransitionProgressRadialCW::create(t, s);
	case 3: return TransitionProgressHorizontal::create(t, s);
	case 4: return TransitionProgressVertical::create(t, s);
	case 5: return TransitionProgressInOut::create(t, s);
	case 6: return TransitionProgressOutIn::create(t, s);

		// ����
	case 7: return TransitionCrossFade::create(t, s);


		// �������ѱ����� : PageTransitionForward
	case 8: return TransitionPageTurn::create(t, s, false);
		// �������ѱ����� : PageTransitionBackward
	case 9: return TransitionPageTurn::create(t, s, true);
		// �ٵ��ǹ��� �����ϴܺ��� ������ܼ����� �����
	case 10: return TransitionFadeTR::create(t, s);
		// �����ǹ��� ������ܺ��� �����ϴܼ����� �����
	case 11: return TransitionFadeBL::create(t, s);
		// �ϴܿ��� ������� �߶�
	case 12: return TransitionFadeUp::create(t, s);
		// ��ܿ��� �ϴ����� �߶�
	case 13: return TransitionFadeDown::create(t, s);


		// �ٵ��ǹ��� �Ѹ���
	case 14: return TransitionTurnOffTiles::create(t, s);


		// ���η� ����� ����
	case 15: return TransitionSplitRows::create(t, s);
		// ���η� ����� ����, �糡�� �εպ��� ������ �������� ����
	case 16: return TransitionSplitCols::create(t, s);


		// ���̵��ξƿ� : ���� ȭ��
	case 17: return TransitionFade::create(t, s);
		// ���̵��ξƿ� : �Ͼ� ȭ��
	case 18: return TransitionFade::create(t, s, Color3B::WHITE);


		// X��(Ⱦ��)�� �������� ȸ�� : FlipXLeftOver
	case 19: return TransitionFlipX::create(t, s, TransitionScene::Orientation::LEFT_OVER);
		// X��(Ⱦ��)�� �������� ȸ�� : FlipXRightOver
	case 20: return TransitionFlipX::create(t, s, TransitionScene::Orientation::RIGHT_OVER);
		// Y��(����)�� �������� ȸ�� : FlipYUpOver
	case 21: return TransitionFlipY::create(t, s, TransitionScene::Orientation::UP_OVER);
		// Y��(����)�� �������� ȸ�� : FlipYDownOver
	case 22: return TransitionFlipY::create(t, s, TransitionScene::Orientation::DOWN_OVER);
		// ���������鼭 ����������� �Ѿ : FlipAngularLeftOver
	case 23: return TransitionFlipAngular::create(t, s, TransitionScene::Orientation::LEFT_OVER);
		// ���������鼭 ����������� �Ѿ : FlipAngularRightOver
	case 24: return TransitionFlipAngular::create(t, s, TransitionScene::Orientation::RIGHT_OVER);


		// X��(Ⱦ��)�� �������� ȸ�� (Ȯ��) : ZoomFlipXLeftOver
	case 25: return TransitionZoomFlipX::create(t, s, TransitionScene::Orientation::LEFT_OVER);
		// X��(Ⱦ��)�� �������� ȸ�� (Ȯ��) : ZoomFlipXRightOver
	case 26: return TransitionZoomFlipX::create(t, s, TransitionScene::Orientation::RIGHT_OVER);
		// Y��(����)�� �������� ȸ�� (Ȯ��) : ZoomFlipYUpOver
	case 27: return TransitionZoomFlipY::create(t, s, TransitionScene::Orientation::UP_OVER);
		// Y��(����)�� �������� ȸ�� (Ȯ��) : ZoomFlipYDownOver
	case 28: return TransitionZoomFlipY::create(t, s, TransitionScene::Orientation::DOWN_OVER);
		// ���������鼭 ����������� �Ѿ (Ȯ��) : ZoomFlipAngularLeftOver
	case 29: return TransitionZoomFlipAngular::create(t, s, TransitionScene::Orientation::LEFT_OVER);
		// ���������鼭 ����������� �Ѿ (Ȯ��) : ZoomFlipAngularRightOver
	case 30: return TransitionZoomFlipAngular::create(t, s, TransitionScene::Orientation::RIGHT_OVER);


		// ������� ���� ������� Ȯ��
	case 31: return TransitionShrinkGrow::create(t, s);
		// ȸ���ϸ鼭 Zoom
	case 32: return TransitionRotoZoom::create(t, s);


		// ���ʿ��� ��������� ��Ÿ���� ��������� ���
	case 33: return TransitionMoveInL::create(t, s);
		// �����ʿ��� ��������� ��Ÿ��
	case 34: return TransitionMoveInR::create(t, s);
		// ���ʿ��� ��������� ��Ÿ��
	case 35: return TransitionMoveInT::create(t, s);
		// �Ʒ��ʿ��� ��������� ��Ÿ��
	case 36: return TransitionMoveInB::create(t, s);


		// ���ʿ��� ��������� ��Ÿ���� ��������� �о
	case 37: return TransitionSlideInL::create(t, s);
		// �����ʿ��� ��������� ��Ÿ���� ��������� �о
	case 38: return TransitionSlideInR::create(t, s);
		// ���ʿ��� ��������� ��Ÿ���� ��������� �о
	case 39: return TransitionSlideInT::create(t, s);
		// �Ʒ��ʿ��� ��������� ��Ÿ���� ��������� �о
	case 40: return TransitionSlideInB::create(t, s);

	default: break;
	}

	return NULL;
}

void SongEnding::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
