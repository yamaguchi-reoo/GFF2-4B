#pragma once
#include "common.h"
#include "PadInput.h"
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
	
	float lenge_x, lenge_y;

	float v;
	float t;
	float g;
	float angle;

	float gauge_x, gauge_y;
	float test_x, test_y;

	float a, b, c;

public:
	Effect();
	~Effect();

	void Update();
	void Draw()const;


};

