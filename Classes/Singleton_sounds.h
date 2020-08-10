#pragma once
#include <stdio.h>
#include <string>
#include <vector>


using namespace std;

class Singleton_sounds
{
private:
	static Singleton_sounds* mpInstance;

	Singleton_sounds();
	~Singleton_sounds();

	string mStringBGMArray[3] = {"","",""};

	string mStringEffectArray[9] = { "","","","","","","","",""};

public:
	static Singleton_sounds* getInstance();

	void ReleaseInstance();

	void Create();

	void PlayEffect(int x);

	void PlayBGM();

	int kick_count = 0;

	int MS = 0;

	int KS = 0;

	int SS = 1;

	int HS = 2;



	float Song_Volume = 0.8;
	float Effect_Volume = 0.8;
};

