#pragma once
#include "BoxCollider.h"

class Player :
	public BoxCollider
{
private:
	float move_speed;		//移動速度(左右)
	float jump_power;		//跳躍力
	float acs[4]; //加速度 0=下方向 1=上方向 2=右方向 3=左方向

	bool onfloor_flg[FLOOR_NUM];	//いずれかの地面に触れているかどうか
	bool touch_ceil_flg;			//いずれかの天井に触れているかどうか
	bool rightwall_flg;			//いずれかの右壁に触れているかどうか
	bool leftwall_flg;			//いずれかの左壁に触れているかどうか
	bool apply_gravity;				//重力を適用するかどうか
	bool jump_flg;					//ジャンプ中か
public:
	Player();
	~Player();
	void Update();
	void Draw()const;
	//重力が働く
	void GiveGravity();
	//減速処理(num = 方向)
	void DecAcs(int num);
	//床に触れている時の処理(num = 当たっている床 _sub = 当たっている床の中心座標)
	void OnFloor(int num,Location _sub);
	//天井に触れた時の処理
	void TouchCeiling();
	//右の壁に触れた時の処理
	void TouchRightWall();	
	//左の壁に触れた時の処理
	void TouchLeftWall();
	//押し出す(num = 当たっている床 _sub = 当たっている床の左上座標)
	void Push(int num,Location _sub_location, Erea _sub_erea);
	//各判定をリセット
	void Reset();
	//プレイヤーの加速量取得 0=下方向 1=上方向 2=右方向 3=左方向
	float GetAcs(int num) { return acs[num]; }
};

