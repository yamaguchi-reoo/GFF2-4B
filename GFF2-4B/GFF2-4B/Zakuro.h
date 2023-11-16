#pragma once
#include "CharaBase.h"
#include "Attack.h"


enum  class ZakuroState {
	IDLE = 0,
	IDLE_RIGHT,
	IDLE_LEFT,
	RIGHT,
	LEFT,
};

//仮想クラス
class Zakuro :public CharaBase
{
private:

	ZakuroState zakuro_state;

	bool attack_flg;	// 攻撃しているか	
	int stop_count;		
	bool spawn_flg;		//スポーンしているか
	bool zakuro_direction;//向き(0 = 右 1 = 左)

	//当たり判定関連
	bool onfloor_flg;	//いずれかの地面に触れているかどうか
	bool rightwall_flg;				//いずれかの右壁に触れているかどうか
	bool leftwall_flg;				//いずれかの左壁に触れているかどうか
	bool apply_gravity;				//重力を適用するかどうか

public:
	Zakuro(float pos_x, float pos_y, bool direction, int _who);
	~Zakuro();

	void Update(GameMain* main)override;
	void Draw()const override;
	void Move(); //左右移動
	void MoveNockBack();//ノックバック
	void ZakuroReset();// 当たり判定のリセット
	//重力が働く
	void ZakuroGiveGravity();
	//押し出す(num = 当たっている床 _sub = 当たっている床の左上座標)
	void ZakuroPush(int num, Location _sub_location, Erea _sub_erea);

	void HitWall();

	//攻撃をスポーンさせるのに必要な情報をまとめる
	AttackData CreateAttactData();
	void Attack(GameMain*main);
	void Stop_Attack() { attack_flg = false; }
	//ダメージ受ける処理
	void ApplyDamage(int num);

	void HitZakuro();

	//スポーンフラグの取得
	int GetSpwanFlg() { return spawn_flg; }
	ColorDate GetColorDate();
};