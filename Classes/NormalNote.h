#pragma once

#include "NoteUnit.h"
#include "cocos2d.h"

using namespace cocos2d;

class NormalNote:public NoteUnit
{
private:

	bool left_on = 0;
	bool right_on = 0;

	float mSpeedScalar = 3.0f;


public:
	NormalNote(){}
	~NormalNote(){}

	void Update(float dt);

	void create(Node* tpParentNode,int r);

	void destroy();

	void left_check();
	void right_check();

	void Target_set(Vec2 target);

};

