#pragma once
class FPSer
{
public:
	FPSer();
	~FPSer();
	int time_a = 0;
	int time_b = 0;
	void CountFPS();
	int count = 0;
	double FPS = 0;
	void Wait(); //FPSの調整
	const int setfps = 60; //FPSの最大値
	const int checknum = 60; //FPS計算の精度
};

