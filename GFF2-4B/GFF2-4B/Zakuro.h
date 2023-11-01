#pragma once
#include "CharaBase.h"
#include "Attack.h"

//仮想クラス
class Zakuro :public CharaBase
{
private:

	Direction direction;

	bool attack_flg;		
	//bool direction;		//顔の向き(0=右向き 1=左向き)
	int stop_count;		
	bool spawn_flg;		//スポーンしているか

public:
	Zakuro();
	~Zakuro();

	void Update(GameMain* main)override;
	void Draw()const override;
	void Move(); //左右移動
	void MoveNockBack();//ノックバック

	//攻撃をスポーンさせるのに必要な情報をまとめる
	AttackData CreateAttactData();
	void Attack(GameMain*main);
	void Stop_Attack() { attack_flg = false; }
	//ダメージ受ける処理
	void ApplyDamage(int num);

	int GetSpwanFlg() { return spawn_flg; }
	ColorDate GetColorDate();
};

