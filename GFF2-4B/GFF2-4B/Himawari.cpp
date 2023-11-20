#include "Himawari.h"
#include "GameMain.h"

#define BULLET_INTERVAL 120		//インターバル
#define RAPID_INTERVAL 9		//連射インターバル	
#define HIMAWARI_GRAVITY  10	// 重力
#define BULLET_NUM_MAX 3		//弾の最大連射数

#define HIMAWARI_IMAGE_SHIFT_X 20		//画像ずらし用
#define HIMAWARI_IMAGE_SHIFT_Y 13		//画像ずらし用

Himawari::Himawari(float pos_x, float pos_y, bool direction, int _who)
{
	himawari_state = HimawariState::SHOOT;

	location.x = pos_x;
	location.y = pos_y;
	erea.height = 100;
	erea.width = 50;
	who = _who;

	image = LoadGraph("resource/images/Enemy/Himawari.png");

	himawari_direction = direction;

	attack_flg = true;
	spawn_flg = false;

	rightwall_flg = false;
	leftwall_flg = false;
	apply_gravity = true;
	onfloor_flg = false;
	
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
	//スポーンしているかつアタックフラグが立っているとき
	if (spawn_flg == false && attack_flg == true)
	{
		if (himawari_state == HimawariState::SHOOT) 
		{
			//攻撃
			Attack(main);
		}
	}
	//床に触れていないなら
	if (apply_gravity == true)
	{
		//重力を与える
		HimawariGiveGravity();
	}
	//各移動用変数をリセット
	HimawariReset();

}

void Himawari::Draw() const
{
	if (spawn_flg == false) 
	{
		//DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0xffff00, TRUE);
		//左向き	
		if (himawari_direction == true) 
		{
			//DrawBoxAA(local_location.x + 40, local_location.y + 10, local_location.x, local_location.y + 40, 0x00ff00, true);
			DrawGraphF(local_location.x, local_location.y - HIMAWARI_IMAGE_SHIFT_X, image, true);
		}
		//右向き
		else if (himawari_direction == false) 
		{
			//DrawBoxAA(local_location.x + erea.width - 40, local_location.y + 10, local_location.x + erea.width, local_location.y + 40, 0x00ff00, true);
			DrawTurnGraphF(local_location.x - HIMAWARI_IMAGE_SHIFT_X, local_location.y - HIMAWARI_IMAGE_SHIFT_Y,image, true);
		}
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
	attack_data.delay = 10;
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
			//攻撃を生成する
			main->SpawnAttack(CreateAttactData());
			if (bullet_num <= 0) {
				bullet_num = BULLET_NUM_MAX;
				attack_interval_count = BULLET_INTERVAL;
			}
		}

	}
}

void Himawari::ApplyDamage(int num)
{
	hp -= num;
	if (hp <= 0) {
		spawn_flg = true;
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

ColorDate Himawari::GetColorDate()
{
	 return Date;
}

