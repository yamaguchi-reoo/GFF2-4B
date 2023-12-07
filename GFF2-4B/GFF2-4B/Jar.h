#pragma once
#include "BoxCollider.h"
class Jar:
	public BoxCollider
{
private:
	bool spawn_flg;
	int jar_image;

	bool onfloor_flg;	//いずれかの地面に触れているかどうか
	bool apply_gravity;		//重力を適用するかどうか
	bool jump_attack;
	bool hidden_flg;			//画像点滅用

	int hp;

public:

	Jar(float pos_x, float pos_y);
	~Jar();

	void Update();
	void Draw()const;

	void JarReset();// 当たり判定のリセット
	//重力が働く
	void JarGiveGravity();
	//押し出す(num = 当たっている床 _sub = 当たっている床の左上座標)
	void Push(int num, Location _sub_location, Erea _sub_erea);

	//ダメージを受ける処理
	void ApplyDamage(int num);
	//スポーンフラグ取得
	int GetSpwnFlg() { return spawn_flg; }

	int GetHp() { return hp; }

	void JumpAttack(bool flg) { jump_attack = flg; }
};

