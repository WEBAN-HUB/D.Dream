#pragma once


class Singleton_data
{
private:
	static Singleton_data *mpInstance;

	Singleton_data();
	~Singleton_data();

public:
	static Singleton_data *getInstance();

	void ReleaseInstance();

	void Display();

	int Life = 0;
	float Time = 0;
	int Score = 0;
	int Stage = 0;
	int BestScore_s1 = 0;
	int BestScore_s3 = 0;
	int BestScore_s5 = 0;

	
	bool stage1_c = false;
	bool stage2_c = false;
	bool stage3_c = false;

	int song1p = 0;
	int song2p = 0;
	int song3p = 0;

	int percent = 0;

	void savepercent(float x);
	void SaveScore();

};

