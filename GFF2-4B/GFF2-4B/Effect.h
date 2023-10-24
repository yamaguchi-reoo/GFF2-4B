#pragma once

#include "common.h"
#include "PadInput.h"

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
	float v; //ベクトル

public:
	Effect();
	~Effect();

	void Curve();

	void Update();
	void Draw()const;


};

