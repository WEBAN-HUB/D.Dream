#include "KickNote.h"
#include "NoteUnit.h"
#include "cocos2d.h"
#include "PlayScene.h"
#include "Singleton_data.h"
#include "Singleton_sounds.h"
#include "SimpleAudioEngine.h"


using namespace CocosDenshion;

using namespace cocos2d;

void KickNote::create(Node* tpParentNode)
{
	target.x = 240;
	target.y = 142;

	

	mpSprite = Sprite::create("ball2.png");
	mpSprite->retain();
	mpSprite->setScale(0.15);

	mVec.y = 142;
	mVec.x = 500;

	
	auto kickAnimation = Animation::create();
	kickAnimation->setDelayPerUnit(0.1f);

	kickAnimation->addSpriteFrameWithFile("ball2.png");
	kickAnimation->addSpriteFrameWithFile("ball2_2.png");
	kickAnimation->addSpriteFrameWithFile("ball2_3.png");
	kickAnimation->addSpriteFrameWithFile("ball2_4.png");
	kickAnimation->addSpriteFrameWithFile("ball2_5.png");
	kickAnimation->addSpriteFrameWithFile("ball2_6.png");
	kickAnimation->addSpriteFrameWithFile("ball2_7.png");
	kickAnimation->addSpriteFrameWithFile("ball2_8.png");

	auto kickAnimate = Animate::create(kickAnimation);
	auto kickRepeatForever = RepeatForever::create(kickAnimate);

	mpSprite->runAction(kickRepeatForever);

	this->setPosition(mVec);
	this->addChild(mpSprite, 100);
	this->DoDead();

	Target_set();

	mpParentNode = tpParentNode;
}

void KickNote::destroy()
{
	this->removeChild(mpSprite);
	if (nullptr != mpSprite)
	{
		mpSprite->release();

		mpSprite = nullptr;
	}
}

void KickNote::Update(float dt)
{



	if (first_fallen == 1 && mIsAlive == 1)
	{
		
		time_c = time_c + dt * 9;
		
		mVec.x = p_vec.x + x_v * time_c;

		mVec.y = p_vec.y + y_v * time_c - (0.5 * g * time_c * time_c);

		this->setPosition(mVec);

	}

	if (mid_on && mIsAlive)
	{
		
		time_c = time_c + dt * 9;
		
		mVec.x = p_vec.x + x_v * time_c;

		mVec.y = p_vec.y + y_v * time_c - (0.5 * g * time_c * time_c);

		this->setPosition(mVec);
	
	}


	if (mVec.y < -150)
	{
		if (mIsAlive)
		{
			Singleton_data::getInstance()->Life = Singleton_data::getInstance()->Life - 1;
			DoDead();
		}

		
	}


}


void KickNote::mid_check()
{
	if (this->DoisCollisionWith(target))
	{
		Singleton_sounds::getInstance()->kick_count++;

		first_fallen = 0;
		mid_on = 1;
		Target_set();

		Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->KS);
		Singleton_data::getInstance()->Score = Singleton_data::getInstance()->Score + 50;

		showParticle(Vec2(240,150));
		showParticle2(Vec2(240, 150));

		if (Singleton_sounds::getInstance()->kick_count == 2)
		{
			if (Singleton_data::getInstance()->Stage == 1 || Singleton_data::getInstance()->Stage == 2)
			{
				Singleton_sounds::getInstance()->PlayBGM();
			}

		}
		else if (Singleton_sounds::getInstance()->kick_count == 4)
		{
			if (Singleton_data::getInstance()->Stage == 3 || Singleton_data::getInstance()->Stage == 4 
				|| Singleton_data::getInstance()->Stage == 5 || Singleton_data::getInstance()->Stage ==  6)
			{
				Singleton_sounds::getInstance()->PlayBGM();
			
			}




		}


	}
}



void KickNote::Target_set()
{
	time_c = 0;
	p_vec = mVec;
	target.y = mVec.y;

	distance = target.x - mVec.x;
	x_v = distance / 16;



	y_v = 0.5 * g * 16;



}