#pragma once
#include "CharaBase.h"
#include "Attack.h"

//仮想クラス
class Zakuro :public CharaBase
{
private:
	Location old_location;	//1フレーム前の座標
	bool zakuro_flg;		//左右移動（false = 左　true =　右）
	bool direction;					//顔の向き(0=右向き 1=左向き)
public:
	Zakuro();
	~Zakuro();

	void Update(GameMain* main)override;
	void Draw()const override;

	//攻撃をスポーンさせるのに必要な情報をまとめる
	AttackData CreateAttactData();
};

