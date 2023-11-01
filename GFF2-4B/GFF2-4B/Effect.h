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

struct SplashColor
{
	float magenta;
	float syan;
	float yellow;
};

class Effect
{
private:

	Splash splash;	//オブジェクト化
	SplashColor s_color;

	bool hit_flg; //テスト用(true->敵に攻撃が当たったとき)

	float v;

	float gauge_x, gauge_y;
	float test_x, test_y;

	float color_date;
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


};

