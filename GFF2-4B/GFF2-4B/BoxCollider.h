#pragma once
#include "dxlib.h"
#include"common.h"

struct AttackData {
	float center_x;		//中心座標(x)
	float center_y;		//中心座標(y)
	float height;		//高さ
	float width;		//幅
	bool who_attack;	//誰の攻撃か（false = 自分 true = 敵）
	int attack_time;	//どれくらい判定がその場に居続けるか
	bool direction;		//X座標を基準にしてどの方向に攻撃を発生させるかの判断(0=右 1=左)
};
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

	//当たり判定 (0,0 = 当たっていない それ以外 = 相手の中心座標)
	bool HitBox(BoxCollider* bCollider);

	//左上座標の取得
	Location GetLocation()const;

	//中心座標の取得
	Location GetCenterLocation()const;

	//直径の取得
	Erea GetErea()const;
};