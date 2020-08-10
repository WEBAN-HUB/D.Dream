#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class NoteUnit:public Node
{
protected:
	bool mIsAlive = false;

	Vec2 mVec;

	Sprite* mpSprite = nullptr;

	float mRadius = 26.0f;

	Node* mpParentNode = nullptr;

	bool first_fallen = 1;

	Vec2 L_Target;
	
	Vec2 R_Target;

	Vec2 p_vec;
	
	float g = 9.8;

	float distance; // �� ���� ������ �Ÿ�

	float first_v;  // �ʱ� �ӵ�

	float y_v; // y�������� �ӵ�

	float x_v; // x�������� �ӵ�

	float time_c = 0;

	int ptcount = 0;

public:
	NoteUnit(){}
	~NoteUnit(){}

	bool IsAlive();

	void SetAlive(bool tIsAlive);

	Vec2 GetVec();

	void SetVec(Vec2 tVec);

	float GetRadius();

	bool DoisCollisionWith(Vec2 tVec);

	void DoDead();

	void DoAlive();

	float normalize_g(float dt);

	void showParticle(cocos2d::Vec2 pPoint);

	void showParticle2(cocos2d::Vec2 pPoint);

	void showParticle3(cocos2d::Vec2 pPoint);


};

