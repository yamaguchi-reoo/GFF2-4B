#pragma once
#include "dxlib.h"
#include"common.h"

//中心座標
struct Location
{
	float x;	//左上座標(x)
	float y;	//左上座標(y)
};

//範囲
struct Erea
{
	float height;	//高さ
	float width;	//幅
};

class BoxCollider
{
protected:
	Location location;	//中心座標
	Erea erea; //範囲
public:

	//当たり判定
	bool HitBox(BoxCollider* bCollider);

	//中心座標の取得
	Location GetLocation()const;

	//半径の取得
	Erea GetErea()const;

	//中心座標の設定
	void SetLocation(Location location);
};