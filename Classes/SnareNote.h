#pragma once

#include "NoteUnit.h"
#include "cocos2d.h"

using namespace cocos2d;

class SnareNote :public NoteUnit
{
private:

	bool mid_on = 0;

	float mSpeedScalar = 3.0f;

	Vec2 target;

public:
	SnareNote() {}
	~SnareNote() {}

	void Update(float dt);

	void create(Node* tpParentNode);

	void destroy();

	void mid_check();


	void Target_set();

};

