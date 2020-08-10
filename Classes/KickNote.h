#pragma once



#include "NoteUnit.h"
#include "cocos2d.h"

using namespace cocos2d;

class KickNote :public NoteUnit
{
private:

	bool mid_on = 0;

	float mSpeedScalar = 3.0f;

	Vec2 target;

	int kick_count = 0;

public:
	KickNote() {}
	~KickNote() {}

	void Update(float dt);

	void create(Node* tpParentNode);

	void destroy();

	void mid_check();
	

	void Target_set();

};

