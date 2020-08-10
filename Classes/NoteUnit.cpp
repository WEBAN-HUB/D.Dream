#include "NoteUnit.h"

bool NoteUnit::IsAlive()
{
	return mIsAlive;
}

void NoteUnit::SetAlive(bool tIsAlive)
{
	mIsAlive = tIsAlive;
}

bool NoteUnit::DoisCollisionWith(Vec2 tVec)
{
	bool tResult = false;

	float tRadiusSum = this->mRadius + 26;

	float tDistance = 0.0f;
	tDistance = sqrtf((this->mVec.x - tVec.x) * (this->mVec.x - tVec.x) + 
		(this->mVec.y - tVec.y) * (this->mVec.y - tVec.y));
	if (tDistance <= tRadiusSum)
	{
		tResult = true;
	}

	return tResult;
}

float NoteUnit::GetRadius()
{
	return mRadius;
}

Vec2 NoteUnit::GetVec()
{
	Vec2 tResult;

	tResult = mVec;

	return tResult;
}

void NoteUnit::SetVec(Vec2 tVec)
{
	mVec = tVec;
}

void NoteUnit::DoDead()
{
	this->setVisible(false);
	mpSprite->setVisible(false);
	
	mIsAlive = false;

}

void NoteUnit::DoAlive()
{
	this->setVisible(true);
	mpSprite->setVisible(true);

	mIsAlive = true;
}

float NoteUnit::normalize_g(float dt)
{
	float tresult;
	tresult = g * dt * dt / 2;

	return tresult;
}

void NoteUnit::showParticle(cocos2d::Vec2 pPoint)
{
	ParticleSystem* tpParticleSys = ParticleSystemQuad::create("Particles/ExplodingRing.plist");
	tpParticleSys->setPosition(pPoint);
	tpParticleSys->setDuration(0.2);
	tpParticleSys->setScale(0.45);
	tpParticleSys->setAutoRemoveOnFinish(true);

	mpParentNode->addChild(tpParticleSys,4);
}

void NoteUnit::showParticle2(cocos2d::Vec2 pPoint)
{
	ParticleSystem* tpParticleSys = ParticleSystemQuad::create("Particles/SmallSun.plist");
	tpParticleSys->setColor(Color3B::BLUE);
	tpParticleSys->setPosition(pPoint);
	tpParticleSys->setDuration(0.2);
	tpParticleSys->setScale(1.5);
	tpParticleSys->setAutoRemoveOnFinish(true);

	mpParentNode->addChild(tpParticleSys, 4);
}

void NoteUnit::showParticle3(cocos2d::Vec2 pPoint)
{
	ParticleSystem* tpParticleSys = ParticleSystemQuad::create("Particles/holly.plist");
	tpParticleSys->setColor(Color3B::BLUE);
	tpParticleSys->setPosition(pPoint);
	tpParticleSys->setDuration(0.2);
	tpParticleSys->setScale(0.9);
	tpParticleSys->setAutoRemoveOnFinish(true);

	mpParentNode->addChild(tpParticleSys, 4);
}