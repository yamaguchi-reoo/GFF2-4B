#include "Zakuro.h"
#include "DxLib.h"
#include "GameMain.h"
#include "common.h"

#define MOVE_SPEED  3	//速度
#define ZAKURO_GRAVITY  5//重力

#define ZAKURO_IMAGE_SHIFT_X 20		//画像ずらし用
#define ZAKURO_IMAGE_SHIFT_Y 12		//画像ずらし用

Zakuro::Zakuro(float pos_x, float pos_y, bool direction,int _who)
{
	zakuro_state = ZakuroState::IDLE;

	location.x = pos_x;
	location.y = pos_y;
	erea.height = 50;
	erea.width = 50;
	speed = MOVE_SPEED;
	who = _who;
	hp = 1;

	image = LoadGraph("resource/images/Enemy/zakuro.png");

	stop_count = 120;

	zakuro_direction = true;
	onfloor_flg = false;
	attack_flg = true;
	spawn_flg = false;
	rightwall_flg = false;
	leftwall_flg = false;
	apply_gravity = true;

	hp = 1;

	Date.magenta = 50.0f;
	Date.cyan = 5.0f;
	Date.yellow = 5.0f;
}
Zakuro::~Zakuro()
{
}
void Zakuro::Update(GameMain* main)
{
	if (spawn_flg == false) 
	{
		if (attack_flg == true) 
		{
			//攻撃
			Attack(main);
			//左右移動
			Move();
		}
		else 
		{
			//ノックバック
			MoveNockBack();
		}
	}
		//床に乗っていたら重力OFF
	if (onfloor_flg == true)
	{
		apply_gravity = false;
		if (zakuro_direction == true)
		{
			zakuro_state = ZakuroState::LEFT;
		}
		else
		{
			zakuro_state = ZakuroState::RIGHT;
		}
	}
	//床に触れていないなら
	if (apply_gravity == true)
	{
		//重力を与える
		ZakuroGiveGravity();
	}
	HitWall();

	if (KeyInput::OnKey(KEY_INPUT_Z)) 
	{
		spawn_flg = false;
	}
	//各移動用変数をリセット
	ZakuroReset();
}

void Zakuro::Draw() const
{
	SetFontSize(20);
	//DrawFormatString(200, 0, 0xffffff, "%f", local_location.x);
	if (spawn_flg == false) 
	{
		switch (zakuro_state)
		{
		case ZakuroState::RIGHT:
			DrawTurnGraphF(local_location.x - ZAKURO_IMAGE_SHIFT_X, local_location.y - ZAKURO_IMAGE_SHIFT_Y, image, true);
			break;
		case ZakuroState::LEFT:
			DrawGraphF(local_location.x - ZAKURO_IMAGE_SHIFT_X, local_location.y - ZAKURO_IMAGE_SHIFT_Y, image, true);
			break;
		case ZakuroState::IDLE_RIGHT:
			DrawTurnGraphF(local_location.x - ZAKURO_IMAGE_SHIFT_X, local_location.y - ZAKURO_IMAGE_SHIFT_Y, image, true);
			break;
		case ZakuroState::IDLE_LEFT:
			DrawGraphF(local_location.x - ZAKURO_IMAGE_SHIFT_X, local_location.y - ZAKURO_IMAGE_SHIFT_Y, image, true);			break;
		default:
			break;
		}
	}
}

void Zakuro::Move()
{
	//左移動
	if (zakuro_state == ZakuroState::LEFT) 
	{
		location.x -= MOVE_SPEED;
		zakuro_direction = true;
	/*	if (location.x < 0) 
		{
			zakuro_state = ZakuroState::RIGHT;
			zakuro_direction = false;
		}*/
	}
	//右移動
	if (zakuro_state == ZakuroState::RIGHT) 
	{
		location.x += MOVE_SPEED;
		zakuro_direction = false;
	/*	if (location.x > SCREEN_WIDTH - 50) 
		{
			zakuro_state = ZakuroState::LEFT;
			zakuro_direction = true;
		}*/
	}
}
void Zakuro::MoveNockBack()
{
	//左移動
	if (zakuro_state == ZakuroState::LEFT) 
	{
		location.x += speed * 0.3f;
	}
	//右移動
	if (zakuro_state == ZakuroState::RIGHT) 
	{
		location.x -= speed * 0.3f;
	}

	if (--stop_count <= 0) 
	{
		attack_flg = true;
		stop_count = 120;
	}
}

void Zakuro::ZakuroReset()
{
	//重力が働くかの判定をリセット
	apply_gravity = true;
	rightwall_flg = false;
	leftwall_flg = false;
	onfloor_flg = false;
}

void Zakuro::ZakuroGiveGravity()
{
	if (zakuro_state == ZakuroState::LEFT)
	{
		zakuro_state = ZakuroState::IDLE_LEFT;
	}
	if (zakuro_state == ZakuroState::RIGHT)
	{
		zakuro_state = ZakuroState::IDLE_RIGHT;
	}
	location.y += ZAKURO_GRAVITY;
}

void Zakuro::Push(int num, Location _sub_location, Erea _sub_erea)
{
	Location z_center = { 0 };
	z_center.x = location.x + (erea.width / 2);
	z_center.y = location.y + (erea.height / 2);

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

void Zakuro::HitWall()
{
	//左の壁にぶつかったら右に移動
	if (leftwall_flg == true) {
		zakuro_state = ZakuroState::RIGHT;
		zakuro_direction = false;
		leftwall_flg = false;
	}
	//右の壁にぶつかったら左に移動
	if (rightwall_flg == true) {
		zakuro_state = ZakuroState::LEFT;
		zakuro_direction = true;
		rightwall_flg = false;
	}
}

AttackData Zakuro::CreateAttactData()
{
	AttackData attack_data;
	attack_data.shift_x = -erea.width;
	attack_data.shift_y = erea.height / 2;
	attack_data.width = erea.width;
	attack_data.height = erea.height;
	attack_data.who_attack = who;
	attack_data.attack_time = 2;
	attack_data.delay = 0;
	attack_data.damage = 1;
	attack_data.attack_type = MELEE;
	attack_data.direction = zakuro_direction;


	return attack_data;
}

void Zakuro::Attack(GameMain* main)
{
	//攻撃を生成する
	main->SpawnAttack(CreateAttactData());
}

void Zakuro::ApplyDamage(int num)
{
	hp -= num;
	if (hp <= 0) {
		spawn_flg = true;
		//プレイヤーが斬った敵の数をカウント
		Score::SetAttackEnemyNum(0);
	}
}

void Zakuro::HitZakuro()
{

	//if (zakuro_state == ZakuroState::RIGHT) {
	//	zakuro_state = ZakuroState::LEFT;
	//}
	zakuro_direction = !zakuro_direction;
	//if (zakuro_state == ZakuroState::LEFT) {
	//	zakuro_state = ZakuroState::RIGHT;
	//}

}

ColorDate Zakuro::GetColorDate()
{
	return Date;
}




