#pragma once
#include "BoxCollider.h"

class Player :
	public BoxCollider
{
private:
	float acs[4]; //加速度 0=下方向 1=上方向 2=右方向 3=左方向

	bool onfloor_flg[FLOOR_NUM];	//いずれかの地面に触れているかどうか
	bool apply_gravity;				//重力を適用するかどうか
public:
	Player();
	~Player();
	void Update();
	void Draw()const;
	//重力が働く
	void GiveGravity();
	//減速処理(num = 方向)
	void DecAcs(int num);
	//床に触れている時の処理(num = 当たっている床)
	void OnFloor(int num);
	//床に触れていない時の処理(num = 当たっている床)
	void NotOnFloor(int num);
	//天井に触れた時の処理
	void TouchCeiling(int num);
	//押し出す(num = 当たっている床 _sub = 当たっている床の中心座標)
	void Push(int num,Location _sub);
};
