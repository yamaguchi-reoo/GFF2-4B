#pragma once
#include "BoxCollider.h"

#define ATTACK_EREA_SHIFT_Y -50	 //攻撃範囲をずらす

class Attack :
	public BoxCollider
{
private:
	AttackData attack_data;		//攻撃に必要な情報格納
	bool attack_flg;			//攻撃が発生しているかのフラグ
	bool can_apply_damage;		//ダメージを与えられるか判断
	bool once;					//一回だけ座標の情報を読みこむ（Bullet用）
	bool cut_flg;				//（ひまわりの弾用）攻撃を切られたか判断
	int cut_time;				//切られた演出をする時間

	int bullet_img[ATTACK_EFFECT_NUM][10];              //エフェクト画像用
	int slash_img[5];							
public:
	Attack();
	~Attack();
	void Update(Location _location, Erea _erea);
	void Draw()const;
	//攻撃を発生させる(_attackdata = 攻撃したプレイヤーもしくは敵の攻撃に必要な情報 _location=発生させたプレイヤーもしくは敵の座標)
	void SpawnAttack(AttackData _attackdata);
	//攻撃が発生しているか判断
	bool GetAttackFlg() { return attack_flg; }
	//各情報を取得
	AttackData GetAttackData() { return attack_data; }
	//ダメージを与えられるか判断
	bool GetCanApplyDamage() { return can_apply_damage; }
	//攻撃を消す
	void DeleteAttack();
	//（ひまわりの弾用）攻撃を切られたと判断する
	void SetCutFlg();
	//（ひまわりの弾用）攻撃を切られた演出中か取得
	bool GetCutFlg() { return cut_flg; }
	//攻撃をプレイヤーの顔側に移動させる
	void SetDirection(bool _dir) { attack_data.direction = _dir; }
};
