#pragma once
#include "BoxCollider.h"

class Attack :
	public BoxCollider
{
private:
	bool attack_flg;	//攻撃が発生しているかのフラグ
	bool who_attack;	//誰の攻撃か（false = 自分 true = 敵）
	int attack_time;	//どれくらい判定がその場に居続けるか
public:
	Attack();
	~Attack();
	void Update(Location _location);
	void Draw()const;
	//攻撃を発生させる(_location = 攻撃したプレイヤーor敵の中心座標)
	void SpawnAttack(Location _location);
};
