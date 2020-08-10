#include "Singleton_sounds.h"
#include <iostream>
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;
using namespace CocosDenshion;
using namespace cocos2d;

Singleton_sounds* Singleton_sounds::mpInstance = nullptr;

Singleton_sounds::Singleton_sounds()
{

}

Singleton_sounds::~Singleton_sounds()
{

}

Singleton_sounds* Singleton_sounds::getInstance()
{
	if (nullptr == mpInstance)
	{
		mpInstance = new Singleton_sounds();
		return mpInstance;
	}
	return mpInstance;
}


void Singleton_sounds::Create()
{
	SimpleAudioEngine::getInstance()->setEffectsVolume(0);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0);


	mStringEffectArray[0] = "Sounds/kick1.wav";
	mStringEffectArray[1] = "Sounds/snare1.wav";
	mStringEffectArray[2] = "Sounds/hat1.wav";
	mStringEffectArray[3] = "Sounds/kick2.wav";
	mStringEffectArray[4] = "Sounds/snare2.wav";
	mStringEffectArray[5] = "Sounds/hat2.wav";
	mStringEffectArray[6] = "Sounds/kick3.wav";
	mStringEffectArray[7] = "Sounds/snare3.wav";
	mStringEffectArray[8] = "Sounds/hat3.wav";







	mStringBGMArray[0] = "Sounds/test.mp3";
	mStringBGMArray[1] = "Sounds/test2.mp3";
	mStringBGMArray[2] = "Sounds/test3.mp3";


	int ti = 0;
	int tCount = 0;

	tCount = 3;
	for (ti = 0; ti < tCount; ti++)
	{
		

		SimpleAudioEngine::getInstance()->preloadBackgroundMusic(mStringBGMArray[ti].c_str());
	}

	tCount = 9;
	for (ti = 0; ti < tCount; ti++)
	{
		SimpleAudioEngine::getInstance()->preloadEffect(mStringEffectArray[ti].c_str());
	}
	

	SimpleAudioEngine::getInstance()->setEffectsVolume(Effect_Volume);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(Song_Volume);


}

void Singleton_sounds::ReleaseInstance()
{
	if (nullptr != mpInstance)
	{
		delete mpInstance;
	}
}

void Singleton_sounds::PlayEffect(int x)
{
	SimpleAudioEngine::getInstance()->playEffect(mStringEffectArray[x].c_str());
}

void Singleton_sounds::PlayBGM()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic(mStringBGMArray[MS].c_str());
}