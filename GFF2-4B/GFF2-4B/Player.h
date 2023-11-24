#pragma once
#include "CharaBase.h"
#include "GameMain.h"
#include "Scroll.h"

#define ATTACK_PATTERN 6  //プレイヤーの攻撃のレパートリー

//循環参照防止
class GameMain;

//プレイヤーの状態
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
	JUMP_ATTACK_RIGHT,
	JUMP_ATTACK_RIGHT_END,
	JUMP_ATTACK_LEFT,
	JUMP_ATTACK_LEFT_END,
	DAMAGE_RIGHT,
	DAMAGE_LEFT,
	DEATH_RIGHT,
	DEATH_LEFT,
};

//プレイヤーの状態(文字列) デバッグ表示用
#ifdef _DEBUG
static char player_state_char[24][256]{
	"IDOL_RIGHT",
	"IDOL_LEFT",
	"MOVE_RIGHT",
	"MOVE_LEFT",
	"JUMP_RIGHT",
	"JUMP_LEFT",
	"FALL_RIGHT",
	"FALL_LEFT",
	"ATTACK_RIGHT_ONE",
	"ATTACK_RIGHT_TWO",
	"ATTACK_RIGHT_THREE",
	"ATTACK_RIGHT_FOUR",
	"ATTACK_LEFT_ONE",
	"ATTACK_LEFT_TWO",
	"ATTACK_LEFT_THREE",
	"ATTACK_LEFT_FOUR",
	"JUMP_ATTACK_RIGHT",
	"JUMP_ATTACK_RIGHT_END",
	"JUMP_ATTACK_LEFT",
	"JUMP_ATTACK_LEFT_END",
	"DAMAGE_RIGHT",
	"DAMAGE_LEFT",
	"DEATH_RIGHT",
	"DEATH_LEFT",
};
#endif

class Player :
	public CharaBase
{
private:

#ifdef _DEBUG
	bool d_inv_flg;					//無敵かどうか（デバッグ用）
#endif
	int frame;						//フレーム測定

	//移動関連
	Location old_location;			//1フレーム前の座標
	Location next_location;			//1フレーム後の座標
	float move_speed;				//移動速度(左右)
	float jump_power;				//跳躍力
	float acs[4];					//加速度 0=下方向 1=上方向 2=右方向 3=左方向
	float acs_max;					//最大加速度
	bool direction;					//顔の向き(0=右向き 1=左向き)
	bool move_flg;					//動ける状態か
	float external_move[4];			//外部から加わるプレイヤーを移動させる力 0=下方向 1=上方向 2=右方向 3=左方向
	bool jump_flg;					//ジャンプ中か
	int player_now_erea;			//自分の座標の周囲にあるステージブロックからしか当たり判定を取らないようにする

	//攻撃関連
	AttackData player_attack_data[ATTACK_NUM * 2];	//プレイヤーの攻撃段階と状態に応じたデータをまとめて格納しておく
	int attack_interval_count;						//攻撃の間隔測定用
	int attack_interval;							//攻撃の間隔
	int ca_interval_count;							//コンボ攻撃の間隔測定用
	int combo_attack_interval;						//コンボ攻撃の間隔
	int attack_step;								//攻撃の段階
	int attack_time;								//攻撃している時間
	int attack_time_count;							//攻撃している時間測定用
	bool attack_motion_flg[ATTACK_NUM];				//攻撃モーション中か判断(0から3＝通常攻撃１から４段目　4=落下攻撃)
	bool attack_anim_flg;							//いずれかの攻撃を行っている最中か判断
	bool powerup_flg;								//強化状態か

	//当たり判定関連
	bool onfloor_flg;				//いずれかの地面に触れているかどうか
	bool touch_ceil_flg;			//いずれかの天井に触れているかどうか
	bool rightwall_flg;				//いずれかの右壁に触れているかどうか
	bool leftwall_flg;				//いずれかの左壁に触れているかどうか
	bool apply_gravity;				//重力を適用するかどうか

	//被弾関連
	bool inv_flg;					//無敵時間かどうか
	bool damage_flg;				//攻撃を喰らったか
	int inv_time;					//無敵時間
	int damage_time;				//モーション再生時間
	bool death_flg;					//死亡したかどうか
	int death_time;					//死亡演出中時間

	//描画関連
	int player_image[35];					//プレイヤー画像
	PlayerState player_state;				//プレイヤーの状態格納
	//攻撃アニメーション画像の描画の順番
	int attack_anim_num[5][12] = { 
		{ 0,0,1,1,2,2,3,4,4,5,5,5} ,
		{ 0,0,1,1,2,2,3,3,4,4,5,5} ,
		{ 0,0,1,1,2,3,4,4,5,5,6,6} ,
		{ 0,0,0,1,1,2,3,4,5,5,5,5} ,
		{ 0,0,0,0,1,-6,-6,-6,-6,-6,-6,-6} ,
		};	
	int player_anim;						//プレイヤー画像アニメーション用
	int attack_anim;						//プレイヤー攻撃アニメーション用
	int player_anim_speed;					//プレイヤーのアニメーション速度
	bool hidden_flg;						//画像点滅用

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
	void OnFloor();

	//押し出す( _sub = 当たっている床の左上座標 _type = 当たった床の種類)
	void Push(Location _sub_location, Erea _sub_erea, int _type);

	//各判定をリセット
	void Reset();

	//プレイヤーの加速量取得 0=下方向 1=上方向 2=右方向 3=左方向
	float GetAcs(int num) { return acs[num]; }

	//強制的なプレイヤーの移動(_direction = 移動する方向(false=右方向 true=左方向) _move=移動量)
	void ForciblyMovePlayer(ScrollData _scroll);

	//ダメージを受けた時の処理(num = ダメージ量)
	void ApplyDamage(GameMain* main,int num);

	//攻撃をスポーンさせるのに必要な情報をまとめる(i = どの攻撃か)
	AttackData CreateAttactData(int i);

	//強化状態に入る
	void SetPowerUp();

	//強化状態を解除する
	void StopPowerUp();

	//攻撃関連の処理
	void Attack(GameMain* main);

	//移動関連の処理
	void Move(GameMain* main);

	//描画関連の変数を動かす処理
	void Anim();

	//プレイヤーの状態の取得
	//int GetPlayerState() { return (int)player_state; }

	//プレイヤーの状態の更新
	void UpdatePlayerState();

	//プレイヤーのHPの取得
	int GetPlayerHP() { return hp; }

	//いずれかの攻撃が行われている最中か判断する
	bool PlayAnyAttack();

	//指定した攻撃のフラグをtrueにし、それ以外のフラグをfalseにする
	void SetAttackFlg(int num);

	//プレイヤーの攻撃データを格納する
	void SetPlayerAttackData();

	//プレイヤーをリスポーンさせる(_location=スポーンさせる場所)
	void Respawn(Location _location);

	//プレイヤーが現在行っている攻撃を取得
	int GetAttackStep() { return attack_step; }

	//プレイヤーが床に触れているか取得
	bool GetOnFloorFlg() { return onfloor_flg; }

	//プレイヤーの顔の向き
	bool GetPlayerDirection() { return direction; }

	//プレイヤーが今居るエリアを取得
	int GetPlayerNowErea() { return player_now_erea; }

	//１マス移動毎に床との当たり判定をチェックする
	void MoveLocation(GameMain* main,float _x, float _y);

	void AddPlayerHp() { hp += 1; }
};

