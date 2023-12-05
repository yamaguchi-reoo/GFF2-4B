#include "Himawari.h"
#include "GameMain.h"

#define BULLET_INTERVAL 120		//インターバル
#define RAPID_INTERVAL 9		//連射インターバル	
#define HIMAWARI_GRAVITY  10	// 重力
#define BULLET_NUM_MAX 3		//弾の最大連射数

#define HIMAWARI_IMAGE_SHIFT_X 20		//画像ずらし用
#define HIMAWARI_IMAGE_SHIFT_Y 14		//画像ずらし用
#define HIMAWARI_ANIM_MOVE 0			//移動アニメーション開始地点
#define HIMAWARI_ANIM_ATTACK 2
#define HIMAWARI_DEATH 3				//死亡アニメーション開始地
#define HIMAWARI_ANIM 20				//次の画像に切り替えるまでの時間（フレーム）
#define HIMAWARI_DEATH_ANIM 10			//次の画像に切り替えるまでの時間（フレーム）


Himawari::Himawari(float pos_x, float pos_y, bool direction, int _who)
{
	anim_frame = 0;
	count = 0;

	himawari_state = HimawariState::LEFT;

	location.x = pos_x;
	location.y = pos_y;
	erea.height = 100;
	erea.width = 50;
	who = _who;
	hp = 2;

	image = LoadGraph("resource/images/Enemy/Himawari.png");
	LoadDivGraph("resource/images/Enemy/Himawari.png", 5, 5, 1, 90, 120, himawari_image);
	himawari_anim = 0;
	himawari_direction = direction;

	attack_flg = true;
	spawn_flg = false;

	rightwall_flg = false;
	leftwall_flg = false;
	apply_gravity = true;
	onfloor_flg = false;
	death_flg = false;
	
	rapid_fire_interval = RAPID_INTERVAL;
	attack_interval_count = BULLET_INTERVAL;
	bullet_num = BULLET_NUM_MAX ;

	Date.magenta = 5.0f;
	Date.cyan = 5.0f;
	Date.yellow = 15.0f;
}

Himawari::~Himawari()
{
}

void Himawari::Update(GameMain* main)
{
	anim_frame++;
	//スポーンしているかつアタックフラグが立っているとき
	if (spawn_flg == false && attack_flg == true)
	{
		//攻撃
		Attack(main);
		//行動
		Move();
	}
	//床に乗っていたら重力OFF
	if (onfloor_flg == true)
	{
		apply_gravity = false;
		//if (himawari_direction == true)
		//{
		//	himawari_state = HimawariState::LEFT;
		//}
		//else
		//{
		//	himawari_state = HimawariState::RIGHT;
		//}
	}
	//床に触れていないなら
	if (apply_gravity == true)
	{
		//重力を与える
		HimawariGiveGravity();
	}
	//各移動用変数をリセット
	HimawariReset();
	//描画関連の変数を動かす
	HimawariAnim();
}

void Himawari::Draw() const
{
	if (spawn_flg == false) 
	{
		switch (himawari_state)
		{
		case HimawariState::IDLE:
			break;
		case HimawariState::RIGHT:
			DrawTurnGraphF(local_location.x - HIMAWARI_IMAGE_SHIFT_X, local_location.y - HIMAWARI_IMAGE_SHIFT_Y, himawari_image[HIMAWARI_ANIM_MOVE + himawari_anim], true);
			break;
		case HimawariState::LEFT:
			DrawGraphF(local_location.x, local_location.y - HIMAWARI_IMAGE_SHIFT_Y, himawari_image[HIMAWARI_ANIM_MOVE + himawari_anim], true);
			break;
		case HimawariState::RIGHT_SHOOT:
			DrawTurnGraphF(local_location.x - HIMAWARI_IMAGE_SHIFT_X, local_location.y - HIMAWARI_IMAGE_SHIFT_Y, himawari_image[HIMAWARI_ANIM_ATTACK], true);
			break;
		case HimawariState::LEFT_SHOOT:
			DrawGraphF(local_location.x, local_location.y - HIMAWARI_IMAGE_SHIFT_Y, himawari_image[HIMAWARI_ANIM_ATTACK], true);
			break;
		case HimawariState::CHARGE:
			break;
		case HimawariState::DEATH:
			DrawGraphF(local_location.x, local_location.y - HIMAWARI_IMAGE_SHIFT_Y, himawari_image[/*HIMAWARI_DEATH + */himawari_anim], true);
			break;
		default:
			break;
		}
	}
}

void Himawari::Move()
{
	//左移動
	if (himawari_state == HimawariState::LEFT)
	{
		himawari_direction = true;
	}
	//右移動
	if (himawari_state == HimawariState::RIGHT)
	{
		himawari_direction = false;
	}
}

void Himawari::HimawariReset()
{
	//重力が働くかの判定をリセット
	apply_gravity = true;
	rightwall_flg = false;
	leftwall_flg = false;
	onfloor_flg = false;
}

void Himawari::HimawariGiveGravity()
{
	location.y += HIMAWARI_GRAVITY;
}

void Himawari::Push(int num, Location _sub_location, Erea _sub_erea)
{
	Location h_center = { 0 };
	h_center.x = location.x + (erea.width / 2);
	h_center.y = location.y + (erea.height / 2);

	//床に触れた時
	if (location.y + erea.height - 12 < _sub_location.y)
	{
		location.y = _sub_location.y - erea.height + 0.1f;
		onfloor_flg = true;
	}
	//右の壁に触れた時
	else if (location.x + erea.width - 10 < _sub_location.x)
	{
		location.x = _sub_location.x - erea.width;

		//右の壁に触れたフラグを立てる
		rightwall_flg = true;
	}
	//左の壁に触れた時
	else if (location.x + 10 > _sub_location.x + _sub_erea.width)
	{
		location.x = _sub_location.x + _sub_erea.width;

		//左の壁に触れたフラグを立てる
		leftwall_flg = true;
	}
	//どっちの壁にも触れていないときの地面すり抜け防止
	else
	{
		location.y = _sub_location.y - erea.height;
		onfloor_flg = true;
	}
}

AttackData Himawari::CreateAttactData()
{

	AttackData attack_data;
	//どの段階の攻撃でも変わらない情報はここで格納する
	attack_data.shift_x = -erea.width;
	attack_data.shift_y = + 15;
	attack_data.who_attack = who;
	attack_data.direction = himawari_direction;
	//弾の大きさ
	attack_data.width = 40;
	attack_data.height = 30;
	//攻撃に関する情報
	attack_data.attack_time = 60;
	attack_data.damage = 1;
	attack_data.delay = 5;
	attack_data.attack_type = BULLET;//MELEE;
	attack_data.effect_type = HIMAWARI_BULLET;

	//右に向いていたらアングルはそのまま
	if (himawari_direction == false)
	{
		attack_data.angle = 0.0f;
	}
	//左に向いていたらアングルを180回転
	else
	{
		attack_data.angle = 0.5f;
	}
	attack_data.speed = 10;

	return attack_data;
	
}

void Himawari::Attack(GameMain* main)
{
	if (--attack_interval_count <= 0)
	{
		if (--rapid_fire_interval <= 0) {
			bullet_num--;
			rapid_fire_interval = RAPID_INTERVAL;

			// 攻撃を生成する
			main->SpawnAttack(CreateAttactData());

			// クールダウン
			if (bullet_num <= 0) {
				bullet_num = BULLET_NUM_MAX;
				attack_interval_count = BULLET_INTERVAL;
			}

			// 弾を発射した後にアニメーションステートを設定
			if (himawari_direction == false)
			{
				himawari_state = HimawariState::RIGHT_SHOOT;
			}
			else
			{
				himawari_state = HimawariState::LEFT_SHOOT;
			}
		}
	}
	else
	{
		// 弾を発射した後の一定時間が経過する前に元のアニメーションステートに戻す
		if (himawari_direction == false)
		{
			himawari_state = HimawariState::RIGHT;
		}
		else
		{
			himawari_state = HimawariState::LEFT;
		}
	}
}

void Himawari::ApplyDamage(int num)
{
	hp -= num;
	if (hp <= 0) {
		death_flg = true;
		//プレイヤーが斬った敵の数をカウント
		Score::SetAttackEnemyNum(2);
	}
}

void Himawari::ReverseDirection()
{
		himawari_direction = false;
}

void Himawari::ObverseDirection()
{
	himawari_direction =true ;
}

void Himawari::HimawariAnim()
{
	if (spawn_flg == false)
	{
		//アニメーション用変数を回す
		if (anim_frame % HIMAWARI_ANIM == 0)
		{
			if (++himawari_anim > 1)
			{
				himawari_anim = 0;
			}
		}
	}
	if (death_flg == true)
	{
		himawari_state = HimawariState::DEATH;
		if (++count > HIMAWARI_DEATH_ANIM)
		{
			himawari_anim = 3;
		}
		if (++count > HIMAWARI_DEATH_ANIM + 20)
		{
			himawari_anim = 4;
		}
		if (++count > HIMAWARI_DEATH_ANIM + 40)
		{
			spawn_flg = true;
		}
	}
	////フラグがtrueになってからcountが12以上になったら
	//if (death_flg == true && ++count >= (HIMAWARI_DEATH_ANIM))
	//{
	//	//スポーンフラグを
	//	spawn_flg = true;
	//	count = 0;
	//}
}

ColorDate Himawari::GetColorDate()
{
	 return Date;
}

