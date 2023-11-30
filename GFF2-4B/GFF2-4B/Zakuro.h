#pragma once
#include "CharaBase.h"

enum  class ZakuroState {
	IDLE = 0,
	IDLE_RIGHT,
	IDLE_LEFT,
	RIGHT,
	LEFT,
	DEATH
};

//仮想クラス
class Zakuro :public CharaBase
{
private:

	ZakuroState zakuro_state;

	int anim_frame;     //アニメーションフレーム測定
	int count;			//カウント

	bool attack_flg;	// 攻撃しているか	
	int stop_count;		
	bool spawn_flg;		//スポーンしているか
	bool zakuro_direction;//向き(0 = 右 1 = 左)
	bool knockback_flg;

	//当たり判定関連
	bool onfloor_flg;	//いずれかの地面に触れているかどうか
	bool rightwall_flg;				//いずれかの右壁に触れているかどうか
	bool leftwall_flg;				//いずれかの左壁に触れているかどうか
	bool apply_gravity;				//重力を適用するかどうか
	bool hit_flg; 

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
	//押し出す( _sub = 当たっている床の左上座標 _type = 当たった床の種類)
	void Push(int num, Location _sub_location, Erea _sub_erea);

	//void Push(Location _sub_location, Erea _sub_erea, int _type);
	void HitWall();

	//攻撃をスポーンさせるのに必要な情報をまとめる
	AttackData CreateAttactData();
	void Attack(GameMain*main);
	//攻撃停止
	void Stop_Attack() { attack_flg = false; }
	//ダメージ受ける処理
	void ApplyDamage(int num);
	//ザクロ同士が当たった時の処理
	void HitZakuro();
	//HPの取得
	int GetHp() { return hp; }
	//スポーンフラグの取得
	int GetSpwnFlg() { return spawn_flg; }

	int GetAttackFlg() { return attack_flg; }
	//アニメーション
	//void ZakuroAnim();
	//向きの反転
	//void ReverseDirection();

	ZakuroState GetZakuroState(){return zakuro_state;}
	ColorDate GetColorDate();

};
