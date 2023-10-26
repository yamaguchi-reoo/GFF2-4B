#pragma once
#include "CharaBase.h"
#include "Attack.h"

//仮想クラス
class Zakuro :public CharaBase
{
private:
	bool attack_flg;		
	bool direction;					//顔の向き(0=右向き 1=左向き)
	int stop_count;
public:
	Zakuro();
	~Zakuro();

	void Update(GameMain* main)override;
	void Draw()const override;

	//攻撃をスポーンさせるのに必要な情報をまとめる
	AttackData CreateAttactData();
	void Attack(GameMain*main);
	void Stop_Attack() { attack_flg = false; }


};

