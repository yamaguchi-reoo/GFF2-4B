#pragma once
#include "dxlib.h"
#include"common.h"

struct AttackData {
	float shift_x;			//X座標にいくつずらすか
	float shift_y;			//Y座標にいくつずらすか
	float height;			//高さ
	float width;			//幅
	int who_attack;			//誰の攻撃か(whoと合わせて使う)
	int attack_time;		//どれくらい判定がその場に居続けるか
	bool direction;			//X座標を基準にしてどの方向に攻撃を発生させるかの判断(0=右 1=左)
	int damage;				//与えるダメージ量
	int delay;				//何フレーム待ってから攻撃するか
	int attack_type;		//攻撃の種類(近接、波状、弾)
	//int effect_type;		//攻撃のアニメーションの種類
	// 
	//攻撃の種類がBULLETの場合この情報も書き込む必要がある
	float speed;			//１フレームにどれだけ前に進むか
	float angle;			//弾の角度(顔の向きに応じて方向が変わるため、0～0.25、0.75～1.0の範囲で指定すると顔の前側へ飛ぶ)
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
	Location location;			//中心座標
	Location local_location;	//画面上での座標
	Erea erea; //範囲
	int who;	//プレイヤーか敵か、敵ならどの種類の何体目かを保存する
public:

	//当たり判定 (0,0 = 当たっていない それ以外 = 相手の中心座標)
	bool HitBox(BoxCollider* bCollider);

	//左上座標の取得
	Location GetLocation()const;

	//中心座標の取得
	Location GetCenterLocation()const;

	//ローカル座標の取得
	Location GetLocalLocation()const;

	//直径の取得
	Erea GetErea()const;

	//プレイヤーか敵か、敵ならどの種類の何体目かを取得する
	int GetWho() { return who; }

	//オブジェクトのワールド座標をスクリーン座標に変換する
	void SetScreenPosition(Location _world_to_screen);
};