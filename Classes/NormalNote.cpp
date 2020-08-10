#include "NormalNote.h"
#include "NoteUnit.h"
#include "cocos2d.h"
#include "Singleton_data.h"
#include "Singleton_sounds.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;


using namespace cocos2d;

void NormalNote::create(Node* tpParentNode,int r)
{
	L_Target.x = 120;
	R_Target.x = 360;

	L_Target.y = 242;
	R_Target.y = 242;

	


	

	mpSprite = Sprite::create("ball.png");
	mpSprite->retain();
	mpSprite->setScale(0.2);

	mVec.y = 242;

	if (r == 0)
	{
		mVec.x = 500;
		Target_set(R_Target);
	}
	else if (r == 1)
	{
		mVec.x = -20;
		Target_set(L_Target);
	}
	
	

	this->setPosition(mVec);
	this->addChild(mpSprite, 100);
	this->DoDead();

	mpParentNode = tpParentNode;
}

void NormalNote::destroy()
{
	this->removeChild(mpSprite);
	if (nullptr != mpSprite)
	{
		mpSprite->release();

		mpSprite = nullptr;
	}
}

void NormalNote::Update(float dt)
{


	if (first_fallen == 1 && mIsAlive == 1)
	{
		time_c = time_c + dt * 9;

		mVec.x = p_vec.x + x_v * time_c;

		mVec.y = p_vec.y + y_v * time_c - (0.5 * g * time_c * time_c);

		this->setPosition(mVec);
	
	}

	if (left_on || right_on)
	{
		if (mIsAlive)
		{
			time_c = time_c + dt * 9;
			mVec.x = p_vec.x + x_v * time_c;

			mVec.y = p_vec.y + y_v * time_c - (0.5 * g * time_c * time_c);


			/*float tRyu = 0.0f;
			tRyu =  - (0.5 * g * time_c * time_c);

			if (tRyu <= -512.0f)
			{			
				tRyu = -512.0f;
			}

			mVec.y = p_vec.y + y_v * time_c + tRyu;
			*/



			this->setPosition(mVec);
	
		}

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

void NormalNote::left_check()
{
	if (this->DoisCollisionWith(L_Target))
	{
		first_fallen = 0;
		right_on = 0;
		left_on = 1;
		R_Target.y = mVec.y;
		Target_set(R_Target);

		Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->HS);
		Singleton_data::getInstance()->Score = Singleton_data::getInstance()->Score + 20;
		showParticle(Vec2(120,250));
		showParticle2(Vec2(120, 250));
	}
}

void NormalNote::right_check()
{
	if (this->DoisCollisionWith(R_Target))
	{
		first_fallen = 0;
		left_on = 0;
		right_on = 1;
		L_Target.y = mVec.y;
		Target_set(L_Target);

		Singleton_sounds::getInstance()->PlayEffect(Singleton_sounds::getInstance()->HS);
		Singleton_data::getInstance()->Score = Singleton_data::getInstance()->Score + 20;
		showParticle(Vec2(360,250));
		showParticle2(Vec2(360, 250));

	}
}


void NormalNote::Target_set(Vec2 target)
{
	time_c = 0;
	p_vec = mVec;

	distance = target.x - mVec.x;
	x_v = distance /16; 
	


	y_v = 0.5 * g * 16;



}