#pragma once
#include "dxlib.h"
#include"common.h"

struct AttackData {
	float x;			//左上座標(x)
	float y;			//左上座標(y)
	float height;		//高さ
	float width;		//幅
	int who_attack;		//誰の攻撃か(whoと合わせて使う)
	int attack_time;	//どれくらい判定がその場に居続けるか
	bool direction;		//X座標を基準にしてどの方向に攻撃を発生させるかの判断(0=右 1=左)
	int damage;			//与えるダメージ量
	int delay;			//何フレーム待ってから攻撃するか
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
	int who;	//プレイヤーか敵か、敵ならどの種類の何体目かを保存する
public:

	//当たり判定 (0,0 = 当たっていない それ以外 = 相手の中心座標)
	bool HitBox(BoxCollider* bCollider);

	//左上座標の取得
	Location GetLocation()const;

	//中心座標の取得
	Location GetCenterLocation()const;

	//直径の取得
	Erea GetErea()const;

	//プレイヤーか敵か、敵ならどの種類の何体目かを取得する
	int GetWho() { return who; }
};