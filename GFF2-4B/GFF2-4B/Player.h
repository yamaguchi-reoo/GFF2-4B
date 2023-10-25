#pragma once
#include "CharaBase.h"
#include "GameMain.h"
#include "Scroll.h"

class GameMain;

enum PlayerState {
	IDOL_RIGHT = 0,
	IDOL_LEFT,
	MOVE_RIGHT,
	MOVE_LEFT,
	JUMP_RIGHT,
	JUMP_LEFT,
	FALL_RIGHT,
	FALL_LEFT,
	ATTACK_RIGHT_ONE,
	ATTACK_RIGHT_TWO,
	ATTACK_RIGHT_THREE,
	ATTACK_RIGHT_FOUR,
	ATTACK_LEFT_ONE,
	ATTACK_LEFT_TWO,
	ATTACK_LEFT_THREE,
	ATTACK_LEFT_FOUR,
	JUMPATTACK_RIGHT,
	JUMPATTACK_RIGHT_END,
	JUMPATTACK_LEFT,
	JUMPATTACK_LEFT_END,
	DAMAGE_RIGHT,
	DAMAGE_LEFT,
	DEATH_RIGHT,
	DEATH_LEFT,
};

class Player :
	public CharaBase
{
private:
	Location old_location;			//1フレーム前の座標
	PlayerState player_state;
	float move_speed;				//移動速度(左右)
	float jump_power;				//跳躍力
	float acs[4];					//加速度 0=下方向 1=上方向 2=右方向 3=左方向
	float acs_max;					//最大加速度
	int attack_interval_count;		//攻撃の間隔測定用
	int attack_interval;			//攻撃の間隔
	int attack_step;				//攻撃の段階
	int attack_time;				//攻撃している時間
	bool attack_motion_flg;			//攻撃モーション中か判断
	bool direction;					//顔の向き(0=右向き 1=左向き)
	bool onfloor_flg[FLOOR_NUM];	//いずれかの地面に触れているかどうか
	bool touch_ceil_flg;			//いずれかの天井に触れているかどうか
	bool rightwall_flg;				//いずれかの右壁に触れているかどうか
	bool leftwall_flg;				//いずれかの左壁に触れているかどうか
	bool apply_gravity;				//重力を適用するかどうか
	bool jump_flg;					//ジャンプ中か
	bool powerup_flg;				//強化状態か
	float external_move[4];			//外部から加わるプレイヤーを移動させる力 0=下方向 1=上方向 2=右方向 3=左方向
public:
	Player();
	~Player();
	void Update(GameMain* main)override;
	void Draw()const override;

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

	//強制的なプレイヤーの移動(_direction = 移動する方向(false=右方向 true=左方向) _move=移動量)
	void ForciblyMovePlayer(ScrollData _scroll);

	//ダメージを受けた時の処理(num = ダメージ量)
	void ApplyDamage(int num);

	//攻撃をスポーンさせるのに必要な情報をまとめる
	AttackData CreateAttactData();

	//強化状態に入る
	void SetPowerUp();

	// 強化状態を解除する
	void StopPowerUp();

	//攻撃関連の処理
	void Attack(GameMain* main);

	//移動関連の処理
	void Move();

	//プレイヤーの状態の取得
	int GetPlayerState() { return (int)player_state; }

	//プレイヤーの状態の更新
	void UpdatePlayerState();

	//プレイヤーのHPの取得
	int GetPlayerHP() { return hp; }
};

