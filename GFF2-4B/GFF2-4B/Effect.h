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
	int color_flg;	//色のFlg

};

class Effect
{
private:

	Splash splash;	//オブジェクト化

	bool hit_flg; //テスト用(true->敵に攻撃が当たったとき)

	float v;

	float gauge_x, gauge_y;
	float test_x, test_y;

	int end_flg;

public:
	Effect();
	~Effect();

	void Update();
	void Draw()const;

	bool HitFlg(bool hit)
	{
		hit_flg = hit;
		return hit_flg; 
	};

	float SetLocation(Location location);
	int InitSplash();

	int EndFlg(int end)
	{
		end_flg = end;
		return end_flg;
	};
};

