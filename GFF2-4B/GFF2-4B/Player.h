#pragma once
#include "BoxCollider.h"

class Player :
	public BoxCollider
{
private:
	float acs[4]; //加速度 0=下方向 1=上方向 2=右方向 3=左方向

	bool onfloor_flg;	//地面に触れているかどうか
public:
	Player();
	~Player();
	void Update();
	void Draw()const;
	//重力が働く
	void GiveGravity();
	//減速処理
	void DecAcs(int num);
	//床に触れている時の処理
	void OnFloor();
	//床に触れていない時の処理
	void NotOnFloor();
	//押し出す
	void Push(int num);
};
