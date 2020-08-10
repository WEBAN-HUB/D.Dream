#include "SnareNote.h"
#include "NoteUnit.h"
#include "cocos2d.h"
#include "PlayScene.h"
#include "Singleton_data.h"
#include "Singleton_sounds.h"
#include "SimpleAudioEngine.h"


using namespace CocosDenshion;
using namespace cocos2d;

void SnareNote::create(Node* tpParentNode)
{
	target.x = 240;
	target.y = 142;



	mpSprite = Sprite::create("ball3.png");
	mpSprite->retain();
	mpSprite->setScale(0.15);
	mVec.y =  142; 
	mVec.x =  -20;



	auto snareAnimation = Animation::create();
	snareAnimation->setDelayPerUnit(0.1f);

	snareAnimation->addSpriteFrameWithFile("ball3.png");
	snareAnimation->addSpriteFrameWithFile("ball3_2.png");
	snareAnimation->addSpriteFrameWithFile("ball3_3.png");
	snareAnimation->addSpriteFrameWithFile("ball3_4.png");
	snareAnimation->addSpriteFrameWithFile("ball3_5.png");
	snareAnimation->addSpriteFrameWithFile("ball3_6.png");
	snareAnimation->addSpriteFrameWithFile("ball3_7.png");
	snareAnimation->addSpriteFrameWithFile("ball3_8.png");

	auto snareAnimate = Animate::create(snareAnimation);
	auto snareRepeatForever = RepeatForever::create(snareAnimate);

	mpSprite->runAction(snareRepeatForever);



	this->setPosition(mVec);
	this->addChild(mpSprite, 100);
	this->DoDead();

	Target_set();

	mpParentNode = tpParentNode;
}

void SnareNote::destroy()
{
	this->removeChild(mpSprite);
	if (nullptr != mpSprite)
	{
		mpSprite->release();

		mpSprite = nullptr;
	}
}

void SnareNote::Update(float dt)
{
	

	if (first_fallen == 1 && mIsAlive == 1)
	{
		time_c = time_c + dt * 9;
		mVec.x = p_vec.x + x_v * time_c;

		mVec.y = p_vec.y + y_v * time_c - (0.5 * g * time_c * time_c);

		this->setPosition(mVec);

	}

	if (mid_on)
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


void SnareNote::mid_check()
{
	if (this->DoisCollisionWith(target))
	{
		first_fallen = 0;
		mid_on = 1;
		Target_set();


		Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->SS);
		Singleton_data::getInstance()->Score = Singleton_data::getInstance()->Score + 50;
		showParticle(Vec2(240,150));
		showParticle2(Vec2(240, 150));
	}
}



void SnareNote::Target_set()
{
	time_c = 0;
	p_vec = mVec;
	target.y = mVec.y;

	distance = target.x - mVec.x;
	x_v = distance / 16;



	y_v = 0.5 * g * 16;



}