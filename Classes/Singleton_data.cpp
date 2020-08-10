#include "Singleton_data.h"
#include <iostream>

Singleton_data* Singleton_data::mpInstance = nullptr;

Singleton_data::Singleton_data()
{

}

Singleton_data::~Singleton_data()
{

}

Singleton_data* Singleton_data::getInstance()
{
	if (nullptr == mpInstance)
	{
		mpInstance = new Singleton_data();
		return mpInstance;
	}
	return mpInstance;
}

void Singleton_data::ReleaseInstance()
{
	if (nullptr != mpInstance)
	{
		delete mpInstance;
	}
}


void Singleton_data::SaveScore()
{
	if (Stage == 1)
	{
		if (BestScore_s1 < Score)
		{
			BestScore_s1 = Score;
		}
	}
	if (Stage == 3)
	{
		if (BestScore_s3 < Score)
		{
			BestScore_s3 = Score;
		}
	}
	if (Stage == 5)
	{
		if (BestScore_s5 < Score)
		{
			BestScore_s5 = Score;
		}
	}
}

void Singleton_data::savepercent(float x)
{
	float p = x / 480;
	p = p * 100;

	percent = p;

	if (Stage == 2)
	{
		if (p > song1p)
		{
			song1p = p;
		}
	}
	else if (Stage == 4)
	{
		if (p > song2p)
		{
			song2p = p;
		}
	}
	else if (Stage == 6)
	{
		if (p > song3p)
		{
			song3p = p;
		}
	}
	
}

void Singleton_data::Display()
{

}