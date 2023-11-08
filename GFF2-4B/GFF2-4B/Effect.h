#pragma once
#include "common.h"
#include "PadInput.h"
#include "CharaBase.h"

#define _USE_MATH_DEFINES
#include <math.h>

//しぶき
struct Splash
{
	float x, y;	//中心座標
	int r;	//半径

};


class Effect
{
private:

	Splash splash;	//オブジェクト化
	ColorDate color_date;

	float v;

	float gauge_x, gauge_y;
	float test_x, test_y;

	int Flg;

public:
	Effect();
	~Effect();

	void Update();
	void Draw()const;

	float SetLocation(Location location);
	

	int SetFlg(int flg)
	{
		Flg = flg;
		return Flg;
	}

	int GetFlg() { return Flg; }

	void SetSplashColor(ColorDate color);
	ColorDate GetSplashColor() { return color_date; }

};

